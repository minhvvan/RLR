// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abnormal.h"
#include "AbnormalBleeding.generated.h"

UCLASS()
class RLR_API UAbnormalBleeding : public UAbnormal
{
	GENERATED_BODY()

public:
	UAbnormalBleeding();

	virtual void ApplyAbnormal(ARLRPlayerCharacter* other, int duration) override;

	UFUNCTION()
	virtual void RemoveAbnormal() override;
};
