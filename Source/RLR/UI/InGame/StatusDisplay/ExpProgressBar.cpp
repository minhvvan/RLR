// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/StatusDisplay/ExpProgressBar.h"
#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "Components/ProgressBar.h"
#include "Structs/UtilStructs.h"
#include "RLR.h"

UExpProgressBar::UExpProgressBar(const FObjectInitializer& ObjectInitializer)
{

}

void UExpProgressBar::NativeConstruct()
{
	Super::NativeConstruct();
	SetUIType(EUIType::EXP_PROGRESS_BAR);
}

void UExpProgressBar::UpdateMaxExp(int32 CurrentLevel)
{
	const FExpTable& Data = GetDataManager()->GetExpData(CurrentLevel);
	if (Data == FExpTable::EmptyExpData)
	{
		RLR_LOG(LogRLR, Log, TEXT("Not Found Exp Data"));
		return;
	}

	maxExp = Data.MaxExp;
}

void UExpProgressBar::UpdateExp(int32 UpdatedExp)
{
	currentExp += UpdatedExp;
	float newPercent = FMath::Clamp(float(currentExp) / maxExp, 0.f, 1.f);

	ExpProgressBar->SetPercent(newPercent);
}

int64 UExpProgressBar::GetMaxExp()
{
	return maxExp;
}

int64 UExpProgressBar::GetCurrentExp()
{
	return currentExp;
}
void UExpProgressBar::ResetCurrentExp()
{
	currentExp = 0;
}