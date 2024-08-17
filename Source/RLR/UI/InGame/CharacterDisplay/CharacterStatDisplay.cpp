// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/CharacterDisplay/CharacterStatDisplay.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "Blueprint/WidgetTree.h"
#include "UI/InGame/CharacterDisplay/AbnormalText.h"

UCharacterStatDisplay::UCharacterStatDisplay(const FObjectInitializer& ObjectInitializer)
{

}

void UCharacterStatDisplay::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCharacterStatDisplay::SetActionSystemComponent(AActor* Owner)
{
	Super::SetActionSystemComponent(Owner);
}

void UCharacterStatDisplay::ShowAbnormal(const FString Text)
{
	if (!AbnormalTextClass) return;
	UAbnormalText* abnormalText = WidgetTree->ConstructWidget<UAbnormalText>(AbnormalTextClass);
	abnormalText->SetAbnormalText(Text);

	OverlayAbnormalText->AddChild(abnormalText);
	abnormalText->PlayWidgetAnim();
}