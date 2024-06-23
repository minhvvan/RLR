// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abnormal.h"
#include "AbnormalProvoke.generated.h"

UCLASS()
class RLR_API UAbnormalProvoke : public UAbnormal
{
	GENERATED_BODY()

public:
	UAbnormalProvoke();

	virtual void ApplyAbnormal(APlayerCharacter* other, int duration) override;

	UFUNCTION()
	virtual void RemoveAbnormal() override;

};
