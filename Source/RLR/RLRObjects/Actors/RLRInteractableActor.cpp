// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRObjects/Actors/RLRInteractableActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/Action/Action.h"
#include "ActionSystem/ActionSystemTypes.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "GameManager/GameplayTagManager.h"
#include "RLR.h"

ARLRInteractableActor::ARLRInteractableActor()
{
	InteractionComp = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionComp"));
	InteractionComp->SetupAttachment(RootComponent);

	//Set Interaction Collision
	InteractionComp->InitSphereRadius(100.f);
	SetRootComponent(InteractionComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);	
	
	InteractUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractUI"));
	InteractUI->SetupAttachment(RootComponent);
	InteractUI->SetRelativeLocation({ 0.f, 0.f, 50.f });
	InteractUI->SetVisibility(false);
	InteractUI->SetDrawSize({50.f, 50.f});
	InteractUI->SetWidgetSpace(EWidgetSpace::Screen);
}

void ARLRInteractableActor::SetInteractData(const FInteractData& Data)
{
	InteractData = Data;
}

void ARLRInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	InteractionComp->OnComponentBeginOverlap.AddDynamic(this, &ARLRInteractableActor::OnBeginOverlap);
	InteractionComp->OnComponentEndOverlap.AddDynamic(this, &ARLRInteractableActor::OnEndOverlap);
}

void ARLRInteractableActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) return;
	if (!GiveToPlayerAction) return;

	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(OtherActor);
	if (!Player) return;

	UActionSystemComponent* PlayerASC = Player->GetActionSystemComponent();
	if (!PlayerASC) return;

	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	FActionSpec Spec(GiveToPlayerAction);
	Spec.bCancelable = true;
	PlayerASC->GiveAction(TagManager.Action_Interaction, Spec);

	InteractUI->SetVisibility(true);
}

void ARLRInteractableActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this) return;

	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(OtherActor);
	if (!Player) return;

	UActionSystemComponent* PlayerASC = Player->GetActionSystemComponent();
	if (!PlayerASC) return;

	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	PlayerASC->RemoveAction(TagManager.Action_Interaction);

	InteractUI->SetVisibility(false);
}