// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abnormal.h"
#include "AbnormalElectric.generated.h"

UCLASS()
class RLR_API UAbnormalElectric : public UAbnormal
{
	GENERATED_BODY()

public:
	UAbnormalElectric();

	virtual void ApplyAbnormal(APlayerCharacter* other, int duration) override;

	UFUNCTION()
	virtual void RemoveAbnormal() override;
};
