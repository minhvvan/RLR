// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/StatusDisplay/ProgressGlobe.h"
#include "Components/Progressbar.h"
#include "Components/Image.h"
#include "Slate/SObjectWidget.h"


void UProgressGlobe::NativeConstruct()
{
	Super::NativeConstruct();
}

void UProgressGlobe::NativeTick(FGeometry MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//InterptGhostGlobe(InDeltaTime);

}

void UProgressGlobe::SetGlobePercent(float Value)
{
	float ProgressPercent = Value;
	if(ProgressPercent < 0)
		ProgressPercent = 0;

	if (GlobeInitialized)
	{
		ProgressBar_Globe->SetPercent(ProgressPercent);
		GlobePercentSet(Value);
	}
	else
	{
		GlobeInitialized = true;
		ProgressBar_Globe->SetPercent(ProgressPercent);
		ProgressBar_Ghost->SetPercent(ProgressPercent);
		GhostPercentTarget = ProgressPercent;
	}
}

void UProgressGlobe::SetGhostPercent(float Value)
{
	ProgressBar_Ghost->SetPercent(Value);
}

void UProgressGlobe::InterptGhostGlobe(float DeltaTime)
{
	float CurrentPercent = ProgressBar_Ghost->GetPercent();

	SetGhostPercent(FMath::FInterpTo(CurrentPercent, GhostPercentTarget, DeltaTime, GhostInterpSpeed));
}
