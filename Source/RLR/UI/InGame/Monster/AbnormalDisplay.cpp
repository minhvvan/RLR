// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Monster/AbnormalDisplay.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSetMonster.h"
#include "RLRObjects/Characters/RLRMonster.h"
#include "ActionSystem/StatSet/StatSet.h"
#include "Blueprint/WidgetTree.h"
#include "UI/InGame/Monster/AbnormalText.h"

UAbnormalDisplay::UAbnormalDisplay(const FObjectInitializer& ObjectInitializer)
{
}

void UAbnormalDisplay::NativeConstruct()
{
}

void UAbnormalDisplay::SetActionSystemComponent(AActor* Owner)
{
	Super::SetActionSystemComponent(Owner);
}

void UAbnormalDisplay::ShowAbnormal(const FString Text)
{
	UAbnormalText* abnormalText = WidgetTree->ConstructWidget<UAbnormalText>(AbnormalTextClass);
	abnormalText->SetAbnormalText(Text);

	OverlayAbnormalText->AddChild(abnormalText);
	abnormalText->PlayWidgetAnim();
}