// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/Proto/Struct.pb.h"
#include "MonsterStructs.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FMonsterStatus
{
	GENERATED_BODY()

	FMonsterStatus() :
		MonsterSeq(-1),
		MonsterName(TEXT("")),
		MonsterLevel(0),
		MonsterExp(0),
		MonsterAttackRate(0),
		MonsterDefence(0),
		MonsterHp(0),
		MonsterAttackRange(0.f),
		MonsterTransform({ 0.f, 0.f, 0.f }),
		MonsterId(0),
		MonsterMapId(-1)
	{}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 MonsterSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString MonsterName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 MonsterLevel;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 MonsterExp;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 MonsterAttackRate;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 MonsterDefence;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 MonsterHp;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MonsterAttackRange;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector MonsterTransform;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 MonsterId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 MonsterMapId;

	FString ToString() const
	{
		FString MonsterString;

		auto AppendStatFloat = [&MonsterString](const FString& StatName, float StatValue)
			{
				if (!MonsterString.IsEmpty()) MonsterString.Append(TEXT("\n"));
				MonsterString.Append(FString::Printf(TEXT("%s = %.2f"), *StatName, StatValue));
			};

		auto AppendStatInt = [&MonsterString](const FString& StatName, int32 StatValue)
			{
				if (!MonsterString.IsEmpty()) MonsterString.Append(TEXT("\n"));
				MonsterString.Append(FString::Printf(TEXT("%s = %d"), *StatName, StatValue));
			};

		auto AppendStatString = [&MonsterString](const FString& StatName, FString StatValue)
			{
				if (!MonsterString.IsEmpty()) MonsterString.Append(TEXT("\n"));
				MonsterString.Append(FString::Printf(TEXT("%s = %s"), *StatName, *StatValue));
			};

		AppendStatInt(TEXT("SEQ"), MonsterSeq);
		AppendStatString(TEXT("Name"), MonsterName);
		AppendStatInt(TEXT("Level"), MonsterLevel);
		AppendStatInt(TEXT("Exp"), MonsterExp);
		AppendStatInt(TEXT("Attack Rate"), MonsterAttackRate);
		AppendStatInt(TEXT("Defence"), MonsterDefence);
		AppendStatFloat(TEXT("Attack Range"), MonsterAttackRange);
		AppendStatFloat(TEXT("X"), MonsterTransform.X);
		AppendStatFloat(TEXT("Y"), MonsterTransform.Y);
		AppendStatFloat(TEXT("Z"), MonsterTransform.Z);
		AppendStatInt(TEXT("Id"), MonsterId);
		AppendStatInt(TEXT("MapId"), MonsterMapId);

		return MonsterString;
	}

	void MakeMonsterData(const Protocol::Monster monsterData);
	static const FMonsterStatus EmptyMonsterData;

	/** Operators */

	FORCEINLINE bool operator==(FMonsterStatus const& Other) const
	{
		if (MonsterId != Other.MonsterId)
			return false;

		return true;
	}
};