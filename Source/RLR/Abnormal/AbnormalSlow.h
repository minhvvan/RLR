// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abnormal.h"
#include "AbnormalSlow.generated.h"

UCLASS()
class RLR_API UAbnormalSlow : public UAbnormal
{
	GENERATED_BODY()

public:
	UAbnormalSlow();

	virtual void ApplyAbnormal(ARLRPlayerCharacter* other, int duration) override;

	UFUNCTION()
	virtual void RemoveAbnormal() override;
};
