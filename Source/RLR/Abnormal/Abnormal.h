// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Abnormal.generated.h"

class ARLRPlayerCharacter;

UCLASS(abstract)
class RLR_API UAbnormal : public UActorComponent
{
	GENERATED_BODY()

public:
	
	virtual void ApplyAbnormal(ARLRPlayerCharacter*,int) PURE_VIRTUAL(UAbnormal::ApplyAbnormal, );
	//TODO : Character, Monster 구분
	virtual void RemoveAbnormal() PURE_VIRTUAL(UAbnormal::RemoveAbnormal, );

protected:

	int CoolTime;
	FTimerHandle Timer;
	FTimerDelegate TimerDelegate;
	ARLRPlayerCharacter* Player;

	//TODO : Delete
	enum class ESubAbnormal
	{
		Burn,
		Poison,
		Slow,
		Bleeding
	};

	enum class EMainAbnormal
	{
		Stun,
		Bind,
		Freeze,
		Stiffen,
		Provoke,
		Electric,
		Silence

	};
};
