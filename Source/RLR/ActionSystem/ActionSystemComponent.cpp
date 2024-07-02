// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/Action/Action.h"
#include "RLR.h"

// Sets default values for this component's properties
UActionSystemComponent::UActionSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
	// ...
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
		//instancePolicy에 따라 달라짐
		UAction* Action = Spec->Action;
		if (Action->GetInstancingPolicy() == EActionInstancingPolicy::NonInstanced)
		{
			//CDO를 통해 Activate
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

			NewActionInstance->TryActivateAction();
		}
	}
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
		RLR_LOG(LogRLR, Log, TEXT("Remove: %s"), *EndedAction->GetName());
		Spec->ActionInstances.Remove(EndedAction);
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

FActionActorInfo* UActionSystemComponent::GetActionActorInfo()
{
	return ActorInfo.Get();
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
	OwnedTags.RemoveTag(GameplayTag);
}