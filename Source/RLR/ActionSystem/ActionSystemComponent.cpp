// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/ActionSystemComponent.h"
#include "RLR.h"

// Sets default values for this component's properties
UActionSystemComponent::UActionSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

void UActionSystemComponent::InitActorInfo(AActor* Owner, AActor* Avatar)
{
	OwnerActor = Owner;
	AvatarActor = Avatar;
}

void UActionSystemComponent::GiveAction(FGameplayTag Tag, FActionSpec Spec)
{
	//Action 추가
	if (GrantedActions.Contains(Tag))
	{
		RLR_LOG(LogRLR, Log, TEXT("Already Exist Action same Tag"));
		return;
	}

	GrantedActions.Add(Tag, Spec);
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
	}
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

//void UActionSystemComponent::GiveAction(FGameplayTag Tag, TSubclassOf<AAction> Action)
//{
//}
//
//void UActionSystemComponent::RemoveAction(FGameplayTag Tag)
//{
//}
//
//void UActionSystemComponent::TryActivateAction(FGameplayTag Tag)
//{
//}
