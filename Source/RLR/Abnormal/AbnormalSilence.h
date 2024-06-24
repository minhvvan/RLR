// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abnormal.h"
#include "AbnormalSilence.generated.h"

UCLASS()
class RLR_API UAbnormalSilence : public UAbnormal
{
	GENERATED_BODY()

public:
	UAbnormalSilence();

	virtual void ApplyAbnormal(APlayerCharacter* other, int duration) override;

	UFUNCTION()
	virtual void RemoveAbnormal() override;
};
