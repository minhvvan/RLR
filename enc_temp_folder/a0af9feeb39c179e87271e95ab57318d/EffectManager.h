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

		/*
		* 이펙트 생성
		*	스킬 이펙트
		*		어떤 공격인지에 따라 이펙트 설정.
		*	피격 이펙트
				피격이 누구인지에 따라 다른 이펙트 설정
		* 이펙트 주기관리
		*	단순 이펙트인지, 오버랩을 해야하는 이펙트인지에 따라 이펙트 기능도 필요하다.
		*	DT 에서 긁어올 수 있는지 체크.
		* 이펙트 삭제
		*	액터에서 처리하는것이 좋아보임.
		*
		* 이펙트 DB 에서 긁어오기
		*
		*
		*/
public:
	UEffectManager();
	void SpawnMonsterHitEffect();
	void SpawnPlayerHitEffect(FVector location);
	/*
	Hit 이펙트 생성을 위한 데이터 종류
	1. 몬스터 Seq
	2. 스킬 종류에 따라 생성하는 이펙트 차이.
	3. 이펙트를 생성할 좌표값. -> 이때 몬스터의 정중앙이아닌 피격 위치를 받아와야할 듯.
	4.

	플레이어가 맞았을때
		1. 몬스터 Seq
		2. 좌표값.
	플레이어가 몬스터를 맞췄을때
		1. 플레이어 스킬 Seq
		2. 좌표값.



	*/

private :
	UNiagaraSystem* effect;
	
	// 임시로 랜덤좌표 이펙트 생성을 위한 값
	FVector GenerateRandomOffset(FVector location);
	void GenerateRandomLocation();
	FVector EffectLocation;
	FTimerHandle TimerHandle;
	float min;
	float max;
	int32 RemainingCalls;
};
