// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/StatSet/StatSetMonster.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "RLRObjects/Characters/RLRMonster.h"
#include "GameManager/GameplayTagManager.h"
#include "RLR.h"

UStatSetMonster::UStatSetMonster()
{
}

void UStatSetMonster::UpdateTransForm(FVector NewTransform)
{
	SetMonsterTransform(NewTransform);

	if (ARLRMonster* monster = Cast<ARLRMonster>(GetOuter()))
	{
		AsyncTask(ENamedThreads::GameThread, [monster, NewTransform]()
			{
				monster->SetActorLocation(NewTransform);
			});
	}
}

void UStatSetMonster::UpdateHp(int32 NewHp)
{
	SetMonsterHp(NewHp);
	OnHpChanged.Broadcast();
}

void UStatSetMonster::ApplyAbnormal(const FAbnormal2& abnormal)
{
	ARLRMonster* monster = Cast<ARLRMonster>(GetOuter());
	if (!monster) return;

	auto* ASC = monster->GetActionSystemComponent();
	if (!ASC) return;

	FAbnormalTimer* newTimer = FAbnormalTimer::MakeTimer(abnormal);
	newTimer->AbnormalTimerHandle.Invalidate();

	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	ASC->AddGameplayTag(TagManager.GetAbnormalTag((int)abnormal.AbnormalType));

	auto abnormlMark = GetAbnormalMark((int)abnormal.AbnormalType);
	monster->DisplayAbnormalText(abnormlMark->AbnormalText);
	if (!HasActivatedTimer())
	{
		monster->DisplayAbnormalFX(abnormlMark->AbnoramlFX);
		newTimer->bDisplayed = true;
	}

	FTimerDelegate AbnormalDelegate = FTimerDelegate::CreateUObject(this, &UStatSetMonster::ExpiredAbnormalTimer, newTimer);
	ASC->GetWorld()->GetTimerManager().SetTimer(newTimer->AbnormalTimerHandle, AbnormalDelegate, abnormal.Duration, false);

	AddAbnormalTimer(newTimer);
}

void UStatSetMonster::ExpiredAbnormalTimer(FAbnormalTimer* ExpiredTimer)
{
	ARLRMonster* monster = Cast<ARLRMonster>(GetOuter());
	if (!monster) return;

	auto* ASC = monster->GetActionSystemComponent();
	if (!ASC) return;

	FAbnormalTimer* lastEndTimer = GetTimerTop();
	if (lastEndTimer != ExpiredTimer && !lastEndTimer->bDisplayed)
	{
		//다음거 표시
		auto abnormlMark = GetAbnormalMark((int)lastEndTimer->AbnormalData.AbnormalType);
		monster->DisplayAbnormalFX(abnormlMark->AbnoramlFX);
		lastEndTimer->bDisplayed = true;
	}
	else
	{
		monster->DisplayAbnormalFX(nullptr);
	}
	
	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	ASC->RemoveGameplayTag(TagManager.GetAbnormalTag((int)ExpiredTimer->AbnormalData.AbnormalType));

	RemoveAbnormalTimer(ExpiredTimer);
}