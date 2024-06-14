// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Abnormal.generated.h"


UCLASS(abstract)
class RLR_API UAbnormal : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void ApplyAbnormal() PURE_VIRTUAL(UAbnormal::ApplyAbnormal, );
	virtual void RemoveAbnormal() PURE_VIRTUAL(UAbnormal::RemoveAbnormal, );

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
