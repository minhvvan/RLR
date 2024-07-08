// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abnormal.h"
#include "AbnormalPoison.generated.h"

UCLASS()
class RLR_API UAbnormalPoison : public UAbnormal
{
	GENERATED_BODY()

public:
	UAbnormalPoison();

	virtual void ApplyAbnormal(ARLRPlayerCharacter* other, int duration) override;

	UFUNCTION()
	virtual void RemoveAbnormal() override;
};
