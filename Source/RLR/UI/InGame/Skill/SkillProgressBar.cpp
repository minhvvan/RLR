// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillProgressBar.h"
#include "Components/ProgressBar.h"

USkillProgressBar::USkillProgressBar(const FObjectInitializer& ObjectInitializer):
	CurrentTime(0.f),
	SkillDuration(0.f),
	bStarted(false)
{
}

void USkillProgressBar::NativeConstruct()
{
	Super::NativeConstruct();

	//Tick 실행
	bStarted = true;
}

void USkillProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bStarted)
	{
		CurrentTime += InDeltaTime;
		float newPercent = CurrentTime / SkillDuration;
		SetPecent(newPercent);
	}
}


void USkillProgressBar::SetPecent(float NewPercent)
{
	float percent = FMath::Clamp(NewPercent, 0.f, 100.f);
	SkillProgressBar->SetPercent(percent);

	if (percent >= 100.f) 
	{
		//Delegate 필요시 추가
		RemoveFromParent();
	}
}
