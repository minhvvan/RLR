// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/CharacterOverhead/AbnormalText.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "Structs/UtilStructs.h"

UAbnormalText::UAbnormalText(const FObjectInitializer& ObjectInitializer)
{
}

void UAbnormalText::SetAbnormalText(const FString Text)
{
	AbnormalText->SetText(FText::FromString(Text));
}

void UAbnormalText::PlayWidgetAnim()
{
	if (!AbnormalTextAnim) return;

	EndDelegate.BindDynamic(this, &UAbnormalText::OnEndedWidgetAnim);
	BindToAnimationFinished(AbnormalTextAnim, EndDelegate);

	PlayAnimation(AbnormalTextAnim);
}

void UAbnormalText::OnEndedWidgetAnim()
{
	RemoveFromParent();
}
