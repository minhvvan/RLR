// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/CharacterOverhead/CharacterOverHead.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "Blueprint/WidgetTree.h"
#include "UI/InGame/CharacterOverhead/AbnormalText.h"
#include "Structs/UtilStructs.h"

UCharacterOverHead::UCharacterOverHead(const FObjectInitializer& ObjectInitializer)
{

}

void UCharacterOverHead::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCharacterOverHead::SetActionSystemComponent(AActor* Owner)
{
	Super::SetActionSystemComponent(Owner);
}

void UCharacterOverHead::ShowAbnormal(const FString Text)
{
	if (!AbnormalTextClass) return;
	UAbnormalText* abnormalText = WidgetTree->ConstructWidget<UAbnormalText>(AbnormalTextClass);
	abnormalText->SetAbnormalText(Text);

	OverlayAbnormalText->AddChild(abnormalText);
	abnormalText->PlayWidgetAnim();
}