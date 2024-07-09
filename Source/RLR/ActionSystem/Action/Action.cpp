// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Action.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionTask/ActionTask.h"
#include "RLR.h"

UAction::UAction() :
	bIsActive(false),
	bIsAbilityEnding(false),
	bIsCancelable(false)
{
	InstancingPolicy = EActionInstancingPolicy::InstancedPerExecution;
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

void UAction::TryActivateAction()
{
	PreActivateAction();
	ActivateAction();
}

void UAction::PreActivateAction()
{
	//Action 실행 전 준비
	bIsActive = true;
	bIsAbilityEnding = false;

	//cancel여부 결정
	//bIsCancelable = true;

	if (UActionSystemComponent* const ASC = CurrentActorInfo->ActionSystemComponent.Get())
	{
		// Add tags
		for (auto AddTag : ActivationOwnedTags)
		{
			ASC->AddGameplayTag(AddTag);
		}
	}
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

	bIsAbilityEnding = true;
	bIsActive = false;

	//Task 관리

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
			UActionSystemComponent* AbilitySystemComponent = OwnerActor->FindComponentByClass<UActionSystemComponent>();
			if (AbilitySystemComponent)
			{
				CurrentActorInfo = AbilitySystemComponent->GetActionActorInfo();
			}
		}
	}
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
	if (bIsActive == false || bIsAbilityEnding == true)
	{
		RLR_LOG(LogRLR, Log, TEXT("EndAction being called multiple times"));
		return false;
	}

	return true;
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
