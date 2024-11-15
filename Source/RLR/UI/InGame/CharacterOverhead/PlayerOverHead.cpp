// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/CharacterOverhead/PlayerOverHead.h"
#include "Components/TextBlock.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "ActionSystem/ActionSystemComponent.h"

void UPlayerOverHead::SetActionSystemComponent(AActor* Owner)
{
	Super::SetActionSystemComponent(Owner);

	UStatSetPlayer* statSet = ActionSystemComponent->GetStatSet<UStatSetPlayer>();
	if (!statSet) return;

	Name->SetText(FText::FromString(statSet->GetNickName()));
}