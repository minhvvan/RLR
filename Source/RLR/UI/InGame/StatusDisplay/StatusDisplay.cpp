// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/StatusDisplay/StatusDisplay.h"
#include "UI/InGame/StatusDisplay/ProgressGlobe.h"
#include "UI/InGame/StatusDisplay/ExpProgressBar.h"

void UStatusDisplay::NativeConstruct()
{
	Super::NativeConstruct();
	SetUIType(EUIType::STATUSDISPLAY);
}

void UStatusDisplay::UpdateTotalStat(const FTotalStatus& NewTotalStatus)
{
	float hpPercent = FMath::Clamp(NewTotalStatus.HP / NewTotalStatus.MAX_HP, 0.f, 1.f);
	float mpPercent = FMath::Clamp(NewTotalStatus.HP / NewTotalStatus.MAX_HP, 0.f, 1.f);

	UpdateHpGlobe(hpPercent);
	UpdateMpGlobe(mpPercent);
}

void UStatusDisplay::UpdateHpGlobe(float NewPercent)
{
	HPGlobe->SetGlobePercent(NewPercent);
}

void UStatusDisplay::UpdateMpGlobe(float NewPercent)
{
	MPGlobe->SetGlobePercent(NewPercent);
}

void UStatusDisplay::UpdateLevel(int32 NewLevel)
{
	ExpProgressBar->UpdateMaxExp(NewLevel);
}

void UStatusDisplay::UpdateExp(int32 NewExp)
{
	ExpProgressBar->UpdateExp(NewExp);
}
