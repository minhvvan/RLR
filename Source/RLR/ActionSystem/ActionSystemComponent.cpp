// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/Action/Action.h"
#include "RLR.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"
#include "Structs/UtilStructs.h"

UActionSystemComponent::UActionSystemComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

// Called when the game starts
void UActionSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActionSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();

	AActor* Owner = GetOwner();
	InitActorInfo(Owner, Owner);
}

void UActionSystemComponent::InitActorInfo(AActor* Owner, AActor* Avatar)
{
	if (!ActorInfo)
	{
		ActorInfo = MakeShareable(new FActionActorInfo());
	}

	ActorInfo->InitFromActor(Owner, Avatar, this);

	//TODO: Avatar 변경 처리
}

void UActionSystemComponent::GiveAction(FGameplayTag Tag, const FActionSpec& Spec)
{
	//Action 추가
	if (GrantedActions.Contains(Tag))
	{
		RLR_LOG(LogRLR, Log, TEXT("Already Exist Action same Tag"));
		return;
	}

	GrantedActions.Add(Tag, Spec);
	FActionSpec& OwnedSpec = GrantedActions[Tag];

	if (Spec.Action->GetInstancingPolicy() == EActionInstancingPolicy::InstancedPerActor)
	{
		UAction* NewActionInstance = CreateNewInstanceOfAction(OwnedSpec);
		NewActionInstance->SetTriggerTag(Tag);
	}
}

void UActionSystemComponent::RemoveAction(FGameplayTag Tag)
{
	//Tag로 Action 제거
	if (auto Spec = GrantedActions.Find(Tag))
	{
		GrantedActions.Remove(Tag);
	}
	else
	{
		RLR_LOG(LogRLR, Log, TEXT("No Action"));
	}
}

void UActionSystemComponent::TryActivateAction(FGameplayTag Tag)
{
	//Find
	if (auto Spec = GrantedActions.Find(Tag))
	{
		UAction* Action = Spec->Action;

		//Check Block
		for (FGameplayTag blockTag : Action->ActivationBlockedTags)
		{
			if (HasMatchingGameplayTag(blockTag))
			{
				//Blocked Action
				return;
			}
		}

		//Cancel Other Action
		for (FGameplayTag cancelTag : Action->ActivationCancelTags)
		{
			TryCancelAction(cancelTag);
		}

		//instancePolicy에 따라 달라짐
		if (Action->GetInstancingPolicy() == EActionInstancingPolicy::NonInstanced)
		{
			//CDO를 통해 Activate
			Action->InitCurrentActorInfoFromASC(this);
			Action->SetTriggerTag(Tag);
			Action->TryActivateAction();
		}
		else if (Action->GetInstancingPolicy() == EActionInstancingPolicy::InstancedPerActor)
		{
			//Spec에 있는 Instance를 통해 Activate
			Spec->ActionInstances[0]->TryActivateAction();
		}
		else if(Action->GetInstancingPolicy() == EActionInstancingPolicy::InstancedPerExecution)
		{
			//새로운 Instance 생성 -> Activate
			UAction* NewActionInstance = CreateNewInstanceOfAction(*Spec);
			if (!NewActionInstance) return;
			NewActionInstance->SetTriggerTag(Tag);

			if (!NewActionInstance->TryActivateAction())
			{
				Spec->ActionInstances.Remove(NewActionInstance);
			}
		}
	}
}

void UActionSystemComponent::ActivateActionForce(const FActionResult& ActionResult)
{
	auto DataManager = GameInstance->GetDataManager();
	if (!DataManager) return;

	const FActionResource& actionResource = DataManager->GetActionResource(ActionResult.ActionSeq);
	if (actionResource == FActionResource::EmptyActionResource) return;

	FGameplayTag Tag = actionResource.ActionTag;
	if (auto Spec = GrantedActions.Find(Tag))
	{
		UAction* Action = Spec->Action;

		//instancePolicy에 따라 달라짐
		if (Action->GetInstancingPolicy() == EActionInstancingPolicy::NonInstanced)
		{
			//CDO를 통해 Activate
			Action->InitCurrentActorInfoFromASC(this);
			Action->SetTriggerTag(Tag);
			Action->ActivateActionForce(ActionResult);
		}
		else if (Action->GetInstancingPolicy() == EActionInstancingPolicy::InstancedPerActor)
		{
			//Spec에 있는 Instance를 통해 Activate
			Spec->ActionInstances[0]->ActivateActionForce(ActionResult);
		}
		else if (Action->GetInstancingPolicy() == EActionInstancingPolicy::InstancedPerExecution)
		{
			//새로운 Instance 생성 -> Activate
			UAction* NewActionInstance = CreateNewInstanceOfAction(*Spec);
			if (!NewActionInstance) return;
			NewActionInstance->SetTriggerTag(Tag);

			NewActionInstance->ActivateActionForce(ActionResult);
			Spec->ActionInstances.Remove(NewActionInstance);
		}
	}
}

void UActionSystemComponent::TryCancelAction(FGameplayTag Tag)
{
	 //if (!GrantedActions.Contains(Tag)) return;
	for (auto& [triggerTag, spec] : GrantedActions)
	{
		if (spec.Action->ActionTag.MatchesTag(Tag))
		{
			auto copied(spec.ActionInstances);
			for (auto ActionInstance : copied)
			{
				if (ActionInstance->GetActionState() != EActionState::STATE_INIT && ActionInstance->GetCancelable())
				{
					ActionInstance->CancelAction();
				}
			}
		}
	}
}

TWeakObjectPtr<UAction> UActionSystemComponent::GetActionInstance(FGameplayTag Tag, int idx)
{
	auto spec = GrantedActions.Find(Tag);
	if (spec == nullptr) return nullptr;

	return MakeWeakObjectPtr<UAction>(spec->ActionInstances[idx]);
}

void UActionSystemComponent::NotifyActionEnded(UAction* EndedAction)
{
	FGameplayTag TriggerTag = EndedAction->GetTriggerTag();
	if (!GrantedActions.Contains(TriggerTag)) return;

	FActionSpec* Spec = GrantedActions.Find(TriggerTag);
	UAction* DefaultAction = Spec->Action;

	if (DefaultAction->GetInstancingPolicy() == EActionInstancingPolicy::InstancedPerExecution)
	{
		//해당 instance 삭제
		Spec->ActionInstances.Remove(EndedAction);
	}

	if (StoredActionData.Contains(TriggerTag))
	{
		StoredActionData.Remove(TriggerTag);
	}
}

UAction* UActionSystemComponent::CreateNewInstanceOfAction(FActionSpec& Spec)
{
	if (!ActorInfo) return nullptr;

	//NewActionInstance 생성
	UAction* ActionInstance = NewObject<UAction>(ActorInfo->OwnerActor.Get(), Spec.Action->GetClass());
	if (!ActionInstance) return nullptr;

	//ActionActorInfo Setting
	ActionInstance->InitCurrentActorInfo();
	Spec.ActionInstances.Add(ActionInstance);

	return ActionInstance;
}

FActionActorInfo* UActionSystemComponent::GetActionActorInfo() const
{
	return ActorInfo.Get();
}

float UActionSystemComponent::PlayMontage(UAction* AnimatingAction, UAnimMontage* Montage, float InPlayRate, FName StartSectionName, float StartTimeSeconds)
{
	float Duration = -1.f;

	UAnimInstance* AnimInstance = ActorInfo.IsValid() ? ActorInfo->GetAnimInstance() : nullptr;
	if (AnimInstance && Montage)
	{
		Duration = AnimInstance->Montage_Play(Montage, InPlayRate, EMontagePlayReturnType::MontageLength, StartTimeSeconds);
		if (Duration > 0.f)
		{
			LocalAnimMontageInfo.AnimMontage = Montage;
			LocalAnimMontageInfo.AnimatingAction = AnimatingAction;

			if (AnimatingAction)
			{
				AnimatingAction->SetCurrentMontage(Montage);
			}

			// Start at a given Section.
			if (StartSectionName != NAME_None)
			{
				AnimInstance->Montage_JumpToSection(StartSectionName, Montage);
			}
		}
	}

	return Duration;
}

UAction* UActionSystemComponent::GetAnimatingAction()
{
	return LocalAnimMontageInfo.AnimatingAction.Get();
}

UAnimMontage* UActionSystemComponent::GetCurrentMontage()
{
	return LocalAnimMontageInfo.AnimMontage.Get();
}

void UActionSystemComponent::CurrentMontageStop(float OverrideBlendOutTime)
{
	UAnimInstance* AnimInstance = ActorInfo.IsValid() ? ActorInfo->GetAnimInstance() : nullptr;
	UAnimMontage* MontageToStop = LocalAnimMontageInfo.AnimMontage;
	bool bShouldStopMontage = AnimInstance && MontageToStop && !AnimInstance->Montage_GetIsStopped(MontageToStop);

	if (bShouldStopMontage)
	{
		const float BlendOutTime = (OverrideBlendOutTime >= 0.0f ? OverrideBlendOutTime : MontageToStop->BlendOut.GetBlendTime());

		AnimInstance->Montage_Stop(BlendOutTime, MontageToStop);
	}
}

void UActionSystemComponent::ClearAnimatingAction(UAction* Action)
{
	if (LocalAnimMontageInfo.AnimatingAction.Get() == Action)
	{
		Action->SetCurrentMontage(nullptr);
		LocalAnimMontageInfo.AnimatingAction = nullptr;
	}
}

void UActionSystemComponent::AddActionData(FGameplayTag Tag, FActionData& Data)
{
	if (!StoredActionData.Contains(Tag))
	{
		StoredActionData.Add({ Tag , Data });
	}
	else
	{
		StoredActionData[Tag] = Data;
	}
}

bool UActionSystemComponent::GetActionData(FGameplayTag Tag, FActionData& Data)
{
	if (StoredActionData.Contains(Tag))
	{
		Data = *StoredActionData.Find(Tag);
		return true;
	}

	return false;
}

bool UActionSystemComponent::ActivateWaitAction()
{
	bool bResult = false;

	for (auto& [Tag, Spec] : GrantedActions)
	{
		for (auto& ActionInstance : Spec.ActionInstances)
		{
			if (ActionInstance->GetActionState() == EActionState::STATE_WAIT_ACTIVATE)
			{
				TryActivateAction(Tag);
				bResult = true;
			}
		}
	}

	return bResult;
}

bool UActionSystemComponent::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return OwnedTags.HasMatchingGameplayTag(TagToCheck);
}

void UActionSystemComponent::AddGameplayTag(const FGameplayTag& GameplayTag, int32 Count)
{
	OwnedTags.AddTag(GameplayTag, Count);
}

void UActionSystemComponent::RemoveGameplayTag(const FGameplayTag& GameplayTag, int32 Count)
{
	if (OwnedTags.GetTagCount(GameplayTag) > 0)
	{
		OwnedTags.RemoveTag(GameplayTag);
	}
}

int UActionSystemComponent::GetGameplayTagCount(FGameplayTag TagToCheck) const
{
	return OwnedTags.GetTagCount(TagToCheck);
}