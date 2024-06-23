// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abnormal.h"
#include "AbnormalStiffen.generated.h"

UCLASS()
class RLR_API UAbnormalStiffen : public UAbnormal
{
	GENERATED_BODY()

public:
	UAbnormalStiffen();

	virtual void ApplyAbnormal(APlayerCharacter* other, int duration) override;

	UFUNCTION()
	virtual void RemoveAbnormal() override;
};
