// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/Proto/Skill.pb.h"
#include "Templates/Tuple.h"
#include "GameplayTagContainer.h"
#include "Structs/PlayerStructs.h"
#include "SkillStructs.generated.h"

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	NORMAL = 0,
	AREA,
	HOLDING,
	CASTING,
	MOVILITY,
	TARGETING,
	CHAIN,
	NONE,
};


UENUM(BlueprintType)
enum class EAbnormalType : uint8
{
	STUN = 0,
	BIND,
	FROZEN,
	STIFFEN,
	PROVOKE,
	ELECTRIC,
	SILENCE,
	BURN,
	POISON,
	SLOW,
	BLEEDING,
	NONE
};

UENUM(BlueprintType)
enum class ESkillGroup : uint8
{
	NORMAL = 0,			//일반
	UNIQUE,					//고유
	ULTIMATE,				//각성기
	NONE,
};

UENUM(BlueprintType)
enum class ESkillKind : uint8		//버프? 디버프?
{
	ACTIVE,
	PASSIVE,
	BUFF,
	DEBUFF,
	NONE,
};

UENUM(BlueprintType)
enum class ECostType : uint8	//코스트 타입
{
	MP,
	HP,
	NONE,
};


class UAction;

USTRUCT(Atomic, BlueprintType)
struct FAbnormal
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	EAbnormalType AbnormalType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Duration;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Power;
};

USTRUCT(Atomic, BlueprintType)
struct FSkillClass : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 SkillSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<UAction> SkillClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> SkillImage;

	void MakeSkillData(Protocol::SkillInfo skill);
	FORCEINLINE bool operator==(FSkillClass const& Other) const
	{
		if (SkillSeq != Other.SkillSeq)
			return false;
		return true;
	}
	static const FSkillClass EmptySkillClass;
};

USTRUCT(Atomic, BlueprintType)
struct FSkillData : public FTableRowBase
{
	GENERATED_BODY()

	FSkillData() {};

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 SkillId = -1; // 1번 유저의 검기: 1001

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 SkillSeq = -1; // 검기: 1

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FGameplayTag SkillTag;

	//텍스트
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FText SkillInfo;

	//타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECharacterMainJobType> MainJobType = ECharacterMainJobType::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ESkillGroup>	SkillGroup = ESkillGroup::NONE;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TEnumAsByte<ESkillType>		SkillType = ESkillType::NONE;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TEnumAsByte<ESkillKind>		SillKind = ESkillKind::NONE;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TEnumAsByte<ECostType>		CostType = ECostType::MP;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 CostValue = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 Level = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 RequiredLevel = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 SkillIdx = -1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float DefaultCoolDown;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float FinalCoolDown;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 SkillDistance = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector SkillRange;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 Damage;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Casting;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Duration;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<FAbnormal> Abnormals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTotalStatus PassiveStatus = FTotalStatus();

	/*
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		스킬 미리보기
	*/

	void MakeSkillData(Protocol::SkillInfo skill);
	static const FSkillData EmptySkillData;

	/** Operators */
	FORCEINLINE bool operator==(FSkillData const& Other) const
	{
		if (SkillId != Other.SkillId)
			return false;

		if (SkillSeq != Other.SkillSeq)
			return false;

		return true;
	}

	FString ToString() const;
};

USTRUCT(BlueprintType)
struct FSkillList
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FSkillData> SkillArray;

	bool Contains(int SkillId)
	{
		bool bResult = false;
		for (auto& skill : SkillArray)
		{
			if (skill.SkillId == SkillId)
			{
				bResult = true;
				break;
			}
		}

		return bResult;
	}

	void Add(const FSkillData& Skill)
	{
		SkillArray.Add(Skill);
	}

	TArray<FSkillData> toArray()
	{
		return SkillArray;
	}
};

template<typename T = FGameplayTag, typename U = FSkillData>
struct FSkillDictionary
{
	UPROPERTY()
	TMap<T, U> SkillDict;

public:
	FORCEINLINE auto begin() { return SkillDict.begin(); }
	FORCEINLINE auto begin() const { return SkillDict.begin(); }
	FORCEINLINE auto end() { return SkillDict.end(); }
	FORCEINLINE auto end() const { return SkillDict.end(); }
	FORCEINLINE void Empty(){SkillDict.Empty(); }

	bool Contains(T key)
	{
		return SkillDict.Contains(key);
	}

	void Add(T key, U Skill)
	{
		SkillDict.Add(key, Skill);
	}

	U& operator[](T key)
	{
		return SkillDict[key];
	}
};

