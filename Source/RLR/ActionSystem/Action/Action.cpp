// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Action.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionTask/ActionTask.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "RLR.h"
#include "ActionSystem/AnimNotify_ActivateAction.h"

UAction::UAction() :
	bIsActive(false),
	bIsActionEnding(false),
	bIsCancelable(false)
{
	InstancingPolicy = EActionInstancingPolicy::InstancedPerExecution;
	ActionState = EActionState::STATE_INIT;
}

UGameplayTasksComponent* UAction::GetGameplayTasksComponent(const UGameplayTask& Task) const
{
	return GetCurrentActorInfo() ? GetCurrentActorInfo()->ActionSystemComponent.Get() : nullptr;
}

AActor* UAction::GetGameplayTaskOwner(const UGameplayTask* Task) const
{
	const FActionActorInfo* Info = GetCurrentActorInfo();
	return Info ? Info->OwnerActor.Get() : nullptr;
}

AActor* UAction::GetGameplayTaskAvatar(const UGameplayTask* Task) const
{
	const FActionActorInfo* Info = GetCurrentActorInfo();
	return Info ? Info->AvatarActor.Get() : nullptr;
}

void UAction::OnGameplayTaskInitialized(UGameplayTask& Task)
{
	UActionTask* ActionTask = Cast<UActionTask>(&Task);
	const FActionActorInfo* ActorInfo = GetCurrentActorInfo();

	if (ActionTask && ActorInfo)
	{
		ActionTask->SetActionSystemComponent(ActorInfo->ActionSystemComponent.Get());
		ActionTask->Action = this;
	}
}

void UAction::OnGameplayTaskActivated(UGameplayTask& Task)
{
	ActiveTasks.Add(&Task);
}

void UAction::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	ActiveTasks.Remove(&Task);
}

bool UAction::TryActivateAction()
{
	bool bPossible = PreActivateAction();
	if (bPossible)
	{
		ActivateAction();
	}

	return bPossible;
}

bool UAction::PreActivateAction()
{
	if (UActionSystemComponent* const ASC = CurrentActorInfo->ActionSystemComponent.Get())
	{
		//Action 실행 전 준비
		bIsActive = true;
		bIsActionEnding = false;

		//cancel여부 결정
		//bIsCancelable = true;

		// Add tags
		AddOwnedTag();
	}
	else
	{
		return false;
	}

	return true;
}

void UAction::ActivateAction()
{
	//Do Someting
}

void UAction::CancelAction()
{
	if (!bIsCancelable) return;

	if (OnGameplayAbilityCancelled.IsBound())
	{
		OnGameplayAbilityCancelled.Broadcast();
	}

	EndAction();
}

void UAction::EndAction()
{
	//Action을 종료할 수 있는지 
	if (!CanEndAction()) return;

	bIsActionEnding = true;
	bIsActive = false;

	//Task 관리
	
	//State
	if (InstancingPolicy == EActionInstancingPolicy::InstancedPerActor)
	{
		ActionState = EActionState::STATE_INIT;
	}
	else if (InstancingPolicy == EActionInstancingPolicy::NonInstanced)
	{
		ActionState = EActionState::STATE_INIT;
	}

	if (UActionSystemComponent* const ASC = CurrentActorInfo->ActionSystemComponent.Get())
	{
		// Remove tags
		for (auto RemoveTag : ActivationOwnedTags)
		{
			ASC->RemoveGameplayTag(RemoveTag);
		}
		//FX 관리
		
		//ASC에서 제거
		ASC->NotifyActionEnded(this);
	}
}

void UAction::InitCurrentActorInfo()
{
	if (CurrentActorInfo == nullptr)
	{
		AActor* OwnerActor = Cast<AActor>(GetOuter());
		if (OwnerActor)
		{
			UActionSystemComponent* ActionSystemComponent = OwnerActor->FindComponentByClass<UActionSystemComponent>();
			if (ActionSystemComponent)
			{
				CurrentActorInfo = ActionSystemComponent->GetActionActorInfo();
			}
		}
	}
}

void UAction::InitCurrentActorInfoFromASC(TObjectPtr<UActionSystemComponent> ASC)
{
	if (CurrentActorInfo) return;
	CurrentActorInfo = ASC->GetActionActorInfo();
}

const FActionActorInfo* UAction::GetCurrentActorInfo() const
{
	return CurrentActorInfo;
}

void UAction::SetTriggerTag(FGameplayTag Tag)
{
	TriggerTag = Tag;
}

EActionInstancingPolicy UAction::GetInstancingPolicy() const
{
	return InstancingPolicy;
}

bool UAction::CanActivateAction()
{
	//실행중이면 실행 불가
	if (bIsActive == true) return false;

	return true;
}

bool UAction::CanEndAction()
{
	if (bIsActive == false || bIsActionEnding == true)
	{
		RLR_LOG(LogRLR, Log, TEXT("EndAction being called multiple times"));
		return false;
	}

	return true;
}

void UAction::AddOwnedTag()
{
	if (UActionSystemComponent* const ASC = CurrentActorInfo->ActionSystemComponent.Get())
	{
		for (auto AddTag : ActivationOwnedTags)
		{
			ASC->AddGameplayTag(AddTag);
		}
	}
}

bool UAction::IsOtherUserAction()
{
	bool result = false;

	auto NetworkManager = GameInstance->GetNetworkManager();
	if (!NetworkManager) return false;

	ARLRPlayerCharacter* Owner = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Owner) return false;

	auto ASC = Owner->GetActionSystemComponent();
	if (!ASC) return false;

	UStatSetPlayer* statSet = ASC->GetStatSet<UStatSetPlayer>();
	if (!statSet) return false;

	if (statSet->GetUserSeq() != NetworkManager->GetUserSeq()) result = true;

	return result;
}

void UAction::OnAnimNotifyTriggered()
{
	for (const auto& notify : ActionMontage->Notifies)
	{
		UAnimNotify_ActivateAction* noti = Cast<UAnimNotify_ActivateAction>(notify.Notify);
		if (!noti) continue;

		//TODO: 모든 Callback을 없애지 말고 해당 Callback만 제거하도록 변경되어야 함
		noti->OnTriggered.Clear();
	}
}

UActionSystemComponent* UAction::GetASCFromActorInfo()
{
	if (!ensure(CurrentActorInfo))
	{
		return nullptr;
	}
	return CurrentActorInfo->ActionSystemComponent.Get();
}

AActor* UAction::GetAvatarActorFromActorInfo() const
{
	if (!ensure(CurrentActorInfo))
	{
		return nullptr;
	}
	return CurrentActorInfo->AvatarActor.Get();
}

void UAction::SetCurrentMontage(UAnimMontage* InCurrentMontage)
{
	CurrentMontage = InCurrentMontage;
}

UAnimMontage* UAction::GetCurrentMontage()
{
	return CurrentMontage;
}
