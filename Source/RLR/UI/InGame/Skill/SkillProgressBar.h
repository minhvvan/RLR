// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "SkillProgressBar.generated.h"

UCLASS()
class RLR_API USkillProgressBar : public UBaseUI
{
	GENERATED_BODY()
public:
	USkillProgressBar(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UProgressBar> SkillProgressBar;

public:
	virtual void NativeConstruct() override;
	void SetSkillDuration(float Duration) { SkillDuration = Duration; }

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	float CurrentTime;
	float SkillDuration;

	void SetPecent(float NewPercent);

	bool bStarted;
};
