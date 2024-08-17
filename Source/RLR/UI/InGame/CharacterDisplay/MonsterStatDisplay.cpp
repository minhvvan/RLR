// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/CharacterDisplay/MonsterStatDisplay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "ActionSystem/StatSet/StatSetMonster.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "RLRObjects/Characters/RLRMonster.h"

UMonsterStatDisplay::UMonsterStatDisplay(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer),
	bCompletedChange(true),
	MaxHp(0),
	CurrentHp(0)
{
}

void UMonsterStatDisplay::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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

void UMonsterStatDisplay::UpdateHp()
{
	float percent = FMath::Clamp(float(CurrentHp) / MaxHp, 0.f, 100.f);
	HpProgressBar->SetPercent(percent);
}

void UMonsterStatDisplay::OnHpChanged()
{
	UStatSetMonster* statSet = ActionSystemComponent->GetStatSet<UStatSetMonster>();
	if (!statSet) return;

	bCompletedChange = false;
	TargetHp = statSet->GetMonsterHp();
}

void UMonsterStatDisplay::SetActionSystemComponent(AActor* Owner)
{
	Super::SetActionSystemComponent(Owner);

	UStatSetMonster* statSet = ActionSystemComponent->GetStatSet<UStatSetMonster>();
	if (!statSet) return;

	MaxHp = statSet->GetMonsterHp();
	CurrentHp = statSet->GetMonsterHp();

	Name->SetText(FText::FromString(statSet->GetMonsterName()));
	UpdateHp();

	statSet->OnHpChanged.AddDynamic(this, &UMonsterStatDisplay::OnHpChanged);
}
