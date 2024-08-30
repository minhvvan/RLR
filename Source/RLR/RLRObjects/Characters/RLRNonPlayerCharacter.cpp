// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRObjects/Characters/RLRNonPlayerCharacter.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "UI/DialogueUI.h"
#include "ActionSystem/ActionSystemTypes.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "GameManager/GameplayTagManager.h"
#include "Structs/ObjectStructs.h"
#include "RLR.h"

ARLRNonPlayerCharacter::ARLRNonPlayerCharacter()
{
	InteractionComp = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionComp"));
	InteractionComp->SetupAttachment(RootComponent);

	//Set Interaction Collision
	InteractionComp->InitSphereRadius(300.f);
}

void ARLRNonPlayerCharacter::SetNPCData(const FNPCData& Data)
{
	TSharedPtr<FNPCData> dataPtr = MakeShared<FNPCData>(Data);
	NPCData = dataPtr.ToWeakPtr();
}

void ARLRNonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InteractionComp->OnComponentBeginOverlap.AddDynamic(this, &ARLRNonPlayerCharacter::OnBeginOverlap);
	InteractionComp->OnComponentEndOverlap.AddDynamic(this, &ARLRNonPlayerCharacter::OnEndOverlap);
}

void ARLRNonPlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) return;

	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(OtherActor);
	if (!Player) return;

	UActionSystemComponent* PlayerASC = Player->GetActionSystemComponent();
	if (!PlayerASC) return;

	if (!NPCData.IsValid()) return;

	for (auto [Tag, Action] : GiveToPlayerActions)
	{
		FActionSpec Spec(Action);
		PlayerASC->GiveAction(Tag, Spec);
	}

	FActionData data;
	data.UIClass = DialogueUI;

	FInteractionData interactionData;
	interactionData.DialogueString = NPCData.Pin().Get()->NPCTalk;
	data.InteractionData = interactionData;

	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	PlayerASC->AddActionData(TagManager.Action_Interaction, data);
}

void ARLRNonPlayerCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this) return;

	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(OtherActor);
	if (!Player) return;

	UActionSystemComponent* PlayerASC = Player->GetActionSystemComponent();
	if (!PlayerASC) return;

	for (auto [Tag, Action] : GiveToPlayerActions)
	{
		PlayerASC->RemoveAction(Tag);
	}
}
