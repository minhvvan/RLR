// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/StatSet.h"
#include "StatSetMonster.generated.h"

#define STAT_ACCESSORS(ClassName, PropertyName, PropertyType) \
		STAT_GETTER(PropertyName, PropertyType) \
		STAT_SETTER(PropertyName, PropertyType)

UCLASS()
class RLR_API UStatSetMonster : public UStatSet
{
	GENERATED_BODY()
	/*
	* FMonsterStatus:
		MonsterSeq(-1),
		MonsterName(TEXT("")),
		MonsterLevel(0),
		MontserExp(0),
		MonsterDamage(0),
		MonsterDefence(0),
		MonsterHp(0),
		MonsterDistance(0.f),
		MonsterTransX(0.f),
		MonsterTransY(0.f),
		MonsterTransZ(0.f),
		MonsterMapId(-1)
	*/

public:
	ALL_STAT_SETTER(FMonsterStatus);
	STAT_ACCESSORS(UStatSetMonster, MonsterSeq, int32);
	STAT_ACCESSORS(UStatSetMonster, MonsterName, FString);
	STAT_ACCESSORS(UStatSetMonster, MonsterLevel, int32);
	STAT_ACCESSORS(UStatSetMonster, MontserExp, int32);
	STAT_ACCESSORS(UStatSetMonster, MonsterDamage, int32);
	STAT_ACCESSORS(UStatSetMonster, MonsterDefence, int32);
	STAT_ACCESSORS(UStatSetMonster, MonsterHp, int32);
	STAT_ACCESSORS(UStatSetMonster, MonsterDistance, float);
	STAT_ACCESSORS(UStatSetMonster, MonsterTransX, float);
	STAT_ACCESSORS(UStatSetMonster, MonsterTransY, float);
	STAT_ACCESSORS(UStatSetMonster, MonsterTransZ, float);
	STAT_ACCESSORS(UStatSetMonster, MonsterMapId, int32);
	STAT_ACCESSORS(UStatSetMonster, MonsterId, int64);

	void UpdateTransForm(float x, float y, float z);
private:
	FMonsterStatus Stat;
};
