// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/StatSet/StatSet.h"
#include "GameManager/RLRStruct.h"
#include "StatSetMonster.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHpChanged);

UCLASS()
class RLR_API UStatSetMonster : public UStatSet
{
	GENERATED_BODY()
public:
	UStatSetMonster();

	ALL_STAT_SETTER(FMonsterStatus);
	STAT_ACCESSORS(UStatSetMonster, FMonsterStatus, MonsterSeq, int32);
	STAT_ACCESSORS(UStatSetMonster, FMonsterStatus, MonsterName, FString);
	STAT_ACCESSORS(UStatSetMonster, FMonsterStatus, MonsterLevel, int32);
	STAT_ACCESSORS(UStatSetMonster, FMonsterStatus, MontserExp, int32);
	STAT_ACCESSORS(UStatSetMonster, FMonsterStatus, MonsterAttackRate, int32);
	STAT_ACCESSORS(UStatSetMonster, FMonsterStatus, MonsterDefence, int32);
	STAT_ACCESSORS(UStatSetMonster, FMonsterStatus, MonsterHp, int32);
	STAT_ACCESSORS(UStatSetMonster, FMonsterStatus, MonsterAttackRange, float);
	STAT_ACCESSORS(UStatSetMonster, FMonsterStatus, MonsterTransform, FVector);
	STAT_ACCESSORS(UStatSetMonster, FMonsterStatus, MonsterMapId, int32);
	STAT_ACCESSORS(UStatSetMonster, FMonsterStatus, MonsterId, int64);

	//일반 자료형 템플릿
	template<typename T>
	void ApplyChangeStat(FStatChangeSpec<T>& ChangeSpec)
	{
		if (ChangeSpec.ChangedStat == GetMonsterHpStat())
		{
			UpdateHp(ChangeSpec.NewValue);
		}
	};

	//Vector에 대한 템플릿 특수화
	template<>
	void ApplyChangeStat(FStatChangeSpec<FVector>& ChangeSpec)
	{
		if (ChangeSpec.ChangedStat == GetMonsterTransformStat())
		{
			UpdateTransForm(ChangeSpec.NewValue);
		}
	};

	//Delegates
	FOnHpChanged OnHpChanged;

	//Abnormal
	void ApplyAbnormal(const FAbnormal2& abnormal) override;
	void ExpiredAbnormalTimer(FAbnormalTimer* ExpiredTimer);

private:
	FMonsterStatus Stat;

protected:
	void UpdateTransForm(FVector NewTransform);
	void UpdateHp(int32 NewHp);

	TMap<EAbnormalType, void(*)(const FAbnormal2&, TObjectPtr<UStatSetMonster>)> AbnormalFunctors;
};