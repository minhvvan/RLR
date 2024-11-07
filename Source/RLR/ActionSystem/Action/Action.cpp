// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Action.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionTask/ActionTask.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/DataManager.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "RLR.h"
#include "ActionSystem/AnimNotify_ActivateAction.h"
#include "Structs/UtilStructs.h"

UAction::UAction() :
	bShouldSendPacket(true),
	RotationSpeed(10.f),
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

void UAction::ActivateActionForce(const FActionResult& ActionResult)
{
	if (ActionState == EActionState::STATE_ACTIVATE) return;

	UAction::PreActivateAction();
	ActionState = EActionState::STATE_ACTIVATE;

	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	UActionSystemComponent* ASC = Player->GetActionSystemComponent();
	if (!ASC) return;

	FActionData Data;
	Data.MousePos = ActionResult.TargetTransform;
	ASC->AddActionData(TriggerTag, Data);
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
	//ActionPacket전송
	if(bShouldSendPacket) SendActionPacket();
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

void UAction::PlayActionMontage()
{
	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	UActionSystemComponent* ASC = Player->GetActionSystemComponent();
	if (!ASC) return;

	AController* Controller = Player->GetController();
	if (!Controller) return;

	FActionData Data;
	if (ASC->GetActionData(TriggerTag, Data))
	{
		Controller->StopMovement();
		Player->SetTargetRotation(Data.MousePos, RotationSpeed);
	}

	for (const auto& notify : ActionMontage->Notifies)
	{
		UAnimNotify_ActivateAction* noti = Cast<UAnimNotify_ActivateAction>(notify.Notify);
		if (!noti) continue;

		noti->OnTriggered.Clear();
		noti->OnTriggered.AddUniqueDynamic(this, &ThisClass::OnAnimNotifyTriggered);
	}

	//Play Montage
	UActionTask_PlayMontage* AT = UActionTask_PlayMontage::CreatePlayMontageTask(this, TEXT("PlaySkillAnim"), ActionMontage);
	AT->OnCompleted.AddUniqueDynamic(this, &ThisClass::OnCompletePlayMontage);
	AT->OnCancelled.AddUniqueDynamic(this, &ThisClass::OnCompletePlayMontage);

	AT->ReadyForActivation();
}

void UAction::OnCompletePlayMontage()
{
	EndAction();
}

void UAction::OnAnimNotifyTriggered()
{
}

void UAction::SendActionPacket()
{
	UNetworkManager* NetworkManager = GameInstance->GetNetworkManager();
	if (!NetworkManager) return;	
	
	UDataManager* DataManager = GameInstance->GetDataManager();
	if (!DataManager) return;

	UActionSystemComponent* ASC = GetASCFromActorInfo();
	if (!ASC) return;

	UStatSetPlayer* statSet = ASC->GetStatSet<UStatSetPlayer>();
	if (!statSet) return;

	FActionResult actionResult;
	FActionData actionData;
	ASC->GetActionData(ActionTag, actionData);

	const FActionResource& actionResource = DataManager->GetActionResourceByTag(ActionTag);
	if (actionResource == FActionResource::EmptyActionResource)
	{
		RLR_LOG(LogRLR, Log, TEXT("Not Found ActionResource"));
		return;
	}

	actionResult.UserSeq = statSet->GetUserSeq();
	actionResult.ActionSeq = actionResource.ActionSeq;
	//TODO: ChannelID GameInstance에서 받아오기
	actionResult.ChannelId = 1;
	actionResult.TargetTransform = actionData.MousePos;

	NetworkManager->SendActionPacket(actionResult);
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
