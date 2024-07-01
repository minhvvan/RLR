// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/ActionSystemComponent.h"

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
