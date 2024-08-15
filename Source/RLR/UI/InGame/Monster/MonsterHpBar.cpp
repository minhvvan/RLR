// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Monster/MonsterHpBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "ActionSystem/StatSet/StatSetMonster.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "RLRObjects/Characters/RLRMonster.h"

UMonsterHpBar::UMonsterHpBar(const FObjectInitializer& ObjectInitializer):
	bCompletedChange(true),
	MaxHp(0),
	CurrentHp(0)
{

}

void UMonsterHpBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMonsterHpBar::SetActionSystemComponent(AActor* Owner)
{
	Super::SetActionSystemComponent(Owner);

	UStatSetMonster* statSet = ActionSystemComponent->GetStatSet<UStatSetMonster>();
	if (!statSet) return;

	MaxHp = statSet->GetMonsterHp();
	CurrentHp = statSet->GetMonsterHp();

	Name->SetText(FText::FromString(statSet->GetMonsterName()));
	UpdateHp();

	statSet->OnHpChanged.AddDynamic(this, &UMonsterHpBar::OnHpChanged);
}

void UMonsterHpBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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

void UMonsterHpBar::UpdateHp()
{
	float percent = FMath::Clamp(float(CurrentHp)/MaxHp, 0.f, 100.f);
	HpProgressBar->SetPercent(percent);
}

void UMonsterHpBar::OnHpChanged()
{
	UStatSetMonster* statSet = ActionSystemComponent->GetStatSet<UStatSetMonster>();
	if (!statSet) return;

	bCompletedChange = false;
	TargetHp = statSet->GetMonsterHp();
}