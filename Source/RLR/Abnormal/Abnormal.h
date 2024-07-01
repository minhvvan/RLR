// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Abnormal.generated.h"

<<<<<<< Updated upstream
class APlayerCharacter;
=======
>>>>>>> Stashed changes

UCLASS(abstract)
class RLR_API UAbnormal : public UActorComponent
{
	GENERATED_BODY()

<<<<<<< Updated upstream
public:
	
	virtual void ApplyAbnormal(APlayerCharacter*,int) PURE_VIRTUAL(UAbnormal::ApplyAbnormal, );
	//TODO : Character, Monster 구분
	virtual void RemoveAbnormal() PURE_VIRTUAL(UAbnormal::RemoveAbnormal, );

protected:

	int CoolTime;
	FTimerHandle Timer;
	FTimerDelegate TimerDelegate;
	APlayerCharacter* Player;

	//TODO : Delete
=======
protected:
	virtual void ApplyAbnormal() PURE_VIRTUAL(UAbnormal::ApplyAbnormal, );
	virtual void RemoveAbnormal() PURE_VIRTUAL(UAbnormal::RemoveAbnormal, );

>>>>>>> Stashed changes
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
