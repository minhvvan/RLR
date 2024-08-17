// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <NiagaraSystem.h>
#include "TimerManager.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EffectManager.generated.h"

/**
 *
 */
UCLASS()
class RLR_API UEffectManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UEffectManager();
	void SpawnMonsterHitEffect();
	void SpawnPlayerHitEffect(FVector location);

private :
	UNiagaraSystem* effect;
	
	// 임시로 랜덤좌표 이펙트 생성을 위한 값
	FVector GetRandomLocation(FVector location);
	void SpawnEffect();
	FVector EffectLocation;
	FTimerHandle TimerHandle;
	float min;
	float max;
	int32 RemainingCalls;
};
