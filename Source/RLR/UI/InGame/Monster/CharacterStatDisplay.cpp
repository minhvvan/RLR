// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Monster/CharacterStatDisplay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "ActionSystem/StatSet/StatSetMonster.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "RLRObjects/Characters/RLRMonster.h"
#include "Blueprint/WidgetTree.h"
#include "UI/InGame/Monster/AbnormalText.h"

UCharacterStatDisplay::UCharacterStatDisplay(const FObjectInitializer& ObjectInitializer):
	bCompletedChange(true),
	MaxHp(0),
	CurrentHp(0)
{

}

void UCharacterStatDisplay::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCharacterStatDisplay::SetActionSystemComponent(AActor* Owner)
{
	Super::SetActionSystemComponent(Owner);

	UStatSetMonster* statSet = ActionSystemComponent->GetStatSet<UStatSetMonster>();
	if (!statSet) return;

	MaxHp = statSet->GetMonsterHp();
	CurrentHp = statSet->GetMonsterHp();

	Name->SetText(FText::FromString(statSet->GetMonsterName()));
	UpdateHp();

	statSet->OnHpChanged.AddDynamic(this, &UCharacterStatDisplay::OnHpChanged);
}

void UCharacterStatDisplay::ShowAbnormal(const FString Text)
{
	UAbnormalText* abnormalText = WidgetTree->ConstructWidget<UAbnormalText>(AbnormalTextClass);
	abnormalText->SetAbnormalText(Text);

	OverlayAbnormalText->AddChild(abnormalText);
	abnormalText->PlayWidgetAnim();
}

void UCharacterStatDisplay::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!bCompletedChange)
	{
		int newHp = FMath::Lerp(TargetHp, CurrentHp, .9f);
		CurrentHp = newHp;

		UpdateHp();
		if (newHp == TargetHp)
		{
			bCompletedChange = true;
		}
	}
}

void UCharacterStatDisplay::UpdateHp()
{
	float percent = FMath::Clamp(float(CurrentHp)/MaxHp, 0.f, 100.f);
	HpProgressBar->SetPercent(percent);
}

void UCharacterStatDisplay::OnHpChanged()
{
	UStatSetMonster* statSet = ActionSystemComponent->GetStatSet<UStatSetMonster>();
	if (!statSet) return;

	bCompletedChange = false;
	TargetHp = statSet->GetMonsterHp();
}