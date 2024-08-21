// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "TimerProgressBar.generated.h"

UCLASS()
class RLR_API UTimerProgressBar : public UBaseUI
{
	GENERATED_BODY()
public:
	UTimerProgressBar(const FObjectInitializer& ObjectInitializer);

	/* 남은 타이머 시간 반환하는 함수 */ 
	float GetRemainingTime() const { return TimerDuration - CurrentTime; }
	
	float GetTimerDuration() const { return TimerDuration; }

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UProgressBar> TimerProgressBar;

public:
	virtual void NativeConstruct() override;
	void SetTimerDuration(float Duration) { TimerDuration = Duration; }

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	void SetPecent(float NewPercent);


	float CurrentTime;
	float TimerDuration;


	bool bStarted;
};
