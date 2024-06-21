// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abnormal.h"
#include "AbnormalBind.generated.h"

UCLASS()
class RLR_API UAbnormalBind : public UAbnormal
{
	GENERATED_BODY()

public:	
	UAbnormalBind();

protected:
	APlayerCharacter* player;

public:	
	virtual void ApplyAbnormal(APlayerCharacter* Player, int duration) override;
	
	UFUNCTION()
	virtual void RemoveAbnormal(APlayerCharacter* Player) override;

};
