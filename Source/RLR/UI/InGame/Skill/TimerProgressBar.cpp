// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/TimerProgressBar.h"
#include "Components/ProgressBar.h"

UTimerProgressBar::UTimerProgressBar(const FObjectInitializer& ObjectInitializer):
	CurrentTime(0.f),
	TimerDuration(0.f),
	bStarted(false)
{
}

void UTimerProgressBar::NativeConstruct()
{
	Super::NativeConstruct();

	//Tick 실행
	bStarted = true;
}

void UTimerProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bStarted)
	{
		CurrentTime += InDeltaTime;
		float newPercent = CurrentTime / TimerDuration;
		SetPecent(newPercent);
	}
}


void UTimerProgressBar::SetPecent(float NewPercent)
{
	float percent = FMath::Clamp(NewPercent, 0.f, 100.f);
	TimerProgressBar->SetPercent(percent);

	if (percent >= 100.f) 
	{
		//Delegate 필요시 추가
		RemoveFromParent();
	}
}
