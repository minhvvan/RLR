// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/StatSet/StatSet.h"
#include "RLRObjects/Characters/RLRCharacter.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/LiteralManager.h"
#include "Structs/SkillStructs.h"
#include "RLR.h"

static bool SortByEndtime(const FAbnormalTimer& a, const FAbnormalTimer& b)
{
	return a < b;
}

UStatSet::UStatSet()
{
	ConstructorHelpers::FObjectFinder<UDataTable> TABLE(*RLRLITERAL.DT_AbnormalMark_Path);
	if (TABLE.Succeeded())
	{
		AbnoramlMarkTable = TABLE.Object;
	}
	else
	{
		RLR_LOG(LogRLR, Log, TEXT("AbnoramlMark Table Can't Load"));
	}
}

void UStatSet::AddAbnormalTimer(FAbnormalTimer* NewTimer)
{
	AbnoramlTimers.Add(NewTimer);
	AbnoramlTimers.HeapSort(SortByEndtime);
}

void UStatSet::ApplyAbnormal(const FAbnormal& abnormal)
{
	ARLRCharacter* RLRCharacter = Cast<ARLRCharacter>(GetOuter());
	if (!RLRCharacter) return;

	auto* ASC = RLRCharacter->GetActionSystemComponent();
	if (!ASC) return;

	FAbnormalTimer* newTimer = FAbnormalTimer::MakeTimer(abnormal);
	newTimer->AbnormalTimerHandle.Invalidate();

	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	ASC->AddGameplayTag(TagManager.GetAbnormalTag((int)abnormal.AbnormalType));

	auto abnormlMark = GetAbnormalMark((int)abnormal.AbnormalType);
	RLRCharacter->DisplayAbnormalText(abnormlMark->AbnormalText);
	if (!HasActivatedTimer())
	{
		RLRCharacter->DisplayAbnormalFX(abnormlMark->AbnoramlFX);
		newTimer->bDisplayed = true;
	}

	FTimerDelegate AbnormalDelegate = FTimerDelegate::CreateUObject(this, &UStatSet::ExpiredAbnormalTimer, newTimer);
	ASC->GetWorld()->GetTimerManager().SetTimer(newTimer->AbnormalTimerHandle, AbnormalDelegate, abnormal.Duration, false);

	AddAbnormalTimer(newTimer);
}

void UStatSet::ExpiredAbnormalTimer(FAbnormalTimer* ExpiredTimer)
{
	ARLRCharacter* RLRCharacter = Cast<ARLRCharacter>(GetOuter());
	if (!RLRCharacter) return;

	auto* ASC = RLRCharacter->GetActionSystemComponent();
	if (!ASC) return;

	FAbnormalTimer* lastEndTimer = GetTimerTop();
	if (lastEndTimer != ExpiredTimer && !lastEndTimer->bDisplayed)
	{
		//다음거 표시
		auto abnormlMark = GetAbnormalMark((int)lastEndTimer->AbnormalType);
		RLRCharacter->DisplayAbnormalFX(abnormlMark->AbnoramlFX);
		lastEndTimer->bDisplayed = true;
	}
	else
	{
		RLRCharacter->DisplayAbnormalFX(nullptr);
	}

	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	ASC->RemoveGameplayTag(TagManager.GetAbnormalTag((int)ExpiredTimer->AbnormalType));

	RemoveAbnormalTimer(ExpiredTimer);
}

void UStatSet::RemoveAbnormalTimer(FAbnormalTimer* NewTimer)
{
	AbnoramlTimers.Remove(NewTimer);
	AbnoramlTimers.HeapSort(SortByEndtime);

	FMemory::Free(NewTimer);
}

FAbnormalTimer* UStatSet::GetTimerTop()
{
	return AbnoramlTimers.HeapTop();
}

const FAbnormalMark* UStatSet::GetAbnormalMark(int AbnormalType)
{
	const FAbnormalMark* Data = AbnoramlMarkTable->FindRow<FAbnormalMark>(*FString::FromInt(AbnormalType), RLRLITERAL.StatSet_EmptyString);
	if (Data == nullptr)
	{
		RLR_LOG(LogRLR, Log, TEXT("Not Found AbnormalMark"));
		return nullptr;
	}

	return Data;
}

bool UStatSet::HasActivatedTimer()
{
	return !AbnoramlTimers.IsEmpty();
}

FAbnormalTimer* FAbnormalTimer::MakeTimer(const FAbnormal& Abnormal)
{
	FAbnormalTimer* newTimer = (FAbnormalTimer*)FMemory::Malloc(sizeof(FAbnormalTimer));
	newTimer->EndTime = FDateTime::UtcNow() + FTimespan::FromSeconds(Abnormal.Duration);

	newTimer->AbnormalType = Abnormal.AbnormalType;
	newTimer->bDisplayed = false;

	return newTimer;
}