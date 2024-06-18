// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abnormal.h"
#include "AbnormalStun.generated.h"


UCLASS()
class RLR_API UAbnormalStun : public UAbnormal
{
	GENERATED_BODY()

public:	
	UAbnormalStun();

public:	
	virtual void ApplyAbnormal(APlayerCharacter* Player) override;
	virtual void RemoveAbnormal(APlayerCharacter* Player) override;
};
