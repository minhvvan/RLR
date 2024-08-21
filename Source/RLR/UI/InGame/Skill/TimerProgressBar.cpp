// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/TimerProgressBar.h"
#include "Components/ProgressBar.h"

/* 의심 1 */
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
/* 문제 : Duration 값이 어디선가 자꾸 0으로 설정됨. 어디일까? */
void UTimerProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bStarted)
	{
		// TimerDuration이 0인지 확인하는 추가 로그
		if (TimerDuration <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("TimerDuration is 0 or negative in NativeTick. Aborting update."));
		}

		CurrentTime += InDeltaTime;
		float newPercent = CurrentTime / TimerDuration;
		
		UE_LOG(LogTemp, Log, TEXT("newPercent : %f, CurrentTime : %f, TimerDuration : %f"), newPercent, CurrentTime, TimerDuration);

		
		SetPecent(newPercent);
	}
}


void UTimerProgressBar::SetPecent(float NewPercent)
{
	float percent = FMath::Clamp(NewPercent, 0.f, 1.0f);
	TimerProgressBar->SetPercent(percent);

	if (percent >= 1.0f) 
	{
		//Delegate 필요시 추가
		RemoveFromParent();
	}
}
