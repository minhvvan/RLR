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

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UProgressBar> TimerProgressBar;

public:
	virtual void NativeConstruct() override;
	void SetTimerDuration(float Duration) { TimerDuration = Duration; }

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	float CurrentTime;
	float TimerDuration;

	void SetPecent(float NewPercent);

	bool bStarted;
};
