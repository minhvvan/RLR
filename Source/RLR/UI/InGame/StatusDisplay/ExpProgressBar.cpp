// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/StatusDisplay/ExpProgressBar.h"
#include "Components/ProgressBar.h"
#include "Structs/UtilStructs.h"
#include "RLR.h"

UExpProgressBar::UExpProgressBar(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UDataTable> ExpDataTable(TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ExpTable.DT_ExpTable'"));
	if (ExpDataTable.Succeeded())
	{
		MaxExpTable = ExpDataTable.Object;
	}
	else
	{
		RLR_LOG(LogRLR, Log, TEXT("ExpTable Can't Load"));
	}
}

void UExpProgressBar::UpdateMaxExp(int32 CurrentLevel)
{
	FExpTable* Data = MaxExpTable->FindRow<FExpTable>(*FString::FromInt(CurrentLevel), TEXT(""));
	if (Data == nullptr)
	{
		RLR_LOG(LogRLR, Log, TEXT("Not Found Exp Data"));
		return;
	}

	maxExp = Data->MaxExp;
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