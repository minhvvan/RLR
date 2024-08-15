// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/StatSet/StatSet.h"
#include "RLR.h"

static bool SortByEndtime(const FAbnormalTimer& a, const FAbnormalTimer& b)
{
	return a < b;
}

UStatSet::UStatSet()
{
	ConstructorHelpers::FObjectFinder<UDataTable> TABLE(TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_AbnormalMark.DT_AbnormalMark'"));
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
	const FAbnormalMark* Data = AbnoramlMarkTable->FindRow<FAbnormalMark>(*FString::FromInt(AbnormalType), TEXT(""));
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

FAbnormalTimer* FAbnormalTimer::MakeTimer(const FAbnormal2& Abnormal)
{
	FAbnormalTimer* newTimer = (FAbnormalTimer*)FMemory::Malloc(sizeof(FAbnormalTimer));
	newTimer->EndTime = FDateTime::UtcNow() + FDateTime(Abnormal.Duration);
	newTimer->AbnormalData = Abnormal;
	newTimer->bDisplayed = false;

	return newTimer;
}