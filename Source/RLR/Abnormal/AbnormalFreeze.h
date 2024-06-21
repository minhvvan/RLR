// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abnormal.h"
#include "AbnormalFreeze.generated.h"

UCLASS()
class RLR_API UAbnormalFreeze : public UAbnormal
{
	GENERATED_BODY()

public:
	UAbnormalFreeze();

	virtual void ApplyAbnormal(APlayerCharacter* other, int duration) override;

	UFUNCTION()
	virtual void RemoveAbnormal() override;
};
