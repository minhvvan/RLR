// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abnormal.h"
#include "AbnormalBurn.generated.h"

UCLASS()
class RLR_API UAbnormalBurn : public UAbnormal
{
	GENERATED_BODY()

public:
	UAbnormalBurn();

	virtual void ApplyAbnormal(ARLRPlayerCharacter* other, int duration) override;

	UFUNCTION()
	virtual void RemoveAbnormal() override;
};
