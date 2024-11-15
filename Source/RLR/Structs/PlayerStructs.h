// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/Proto/Struct.pb.h"
#include "Network/Proto/User_2.pb.h"
#include "Network/Proto/Player_2.pb.h"
#include "PlayerStructs.generated.h"

UENUM(BlueprintType)
enum class ECharacterMainJobType : uint8
{
	SWORDSMAN,
	THEIF,
	MAGE,
	ARCHER,
	PRIEST,
	NONE,
};

UENUM(BlueprintType)
enum class ECharacterSubJobType : uint8
{
	/*
		대장장이 등등 추가 예정.
	*/


	NONE,
};


USTRUCT(Atomic, BlueprintType)
struct FSetStatus
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserHP;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserMP;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserSTR;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserAGI;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserINT;

	void MakeSetStatus(Protocol::UserSetStatus Data);
};

USTRUCT(Atomic, BlueprintType)
struct FTotalStatus
{
	GENERATED_BODY()
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float HP = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float HP_ABSORB = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MP = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MP_ABSORB = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float STRENGTH = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float AGILITY = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float INTELLIGENCE = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MAX_HP = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MAX_MP = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float ATTACK = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float DEFENCE = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float ATTACK_SPEED = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MOVE_SPEED = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float LIFE_STEAL = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float CRITICAL_CHANCE = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float CRITICAL_DAMAGE = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float AVOID = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float COOLDOWN_REDUCTION = 0;

	void SetHP(float HP);
	/*
		날라온 패킷을 바꿔준다.
	*/
	void MakeStatus(Protocol::UserTotalStatus Status);

	FString ToString() const
	{
		FString StatString;

		auto AppendStat = [&StatString](const FString& StatName, float StatValue)
			{
				if (StatValue != 0.f)
				{
					if (!StatString.IsEmpty())
					{
						StatString.Append(TEXT(" "));
					}
					StatString.Append(FString::Printf(TEXT("%s = %.2f"), *StatName, StatValue));
				}
			};

		AppendStat(TEXT("HP"), HP);
		AppendStat(TEXT("HP_ABSORB"), HP_ABSORB);
		AppendStat(TEXT("MP"), MP);
		AppendStat(TEXT("MP_ABSORB"), MP_ABSORB);
		AppendStat(TEXT("STRENGTH"), STRENGTH);
		AppendStat(TEXT("AGILITY"), AGILITY);
		AppendStat(TEXT("INTELLIGENCE"), INTELLIGENCE);
		AppendStat(TEXT("MAX_HP"), MAX_HP);
		AppendStat(TEXT("MAX_MP"), MAX_MP);
		AppendStat(TEXT("ATTACK"), ATTACK);
		AppendStat(TEXT("DEFENCE"), DEFENCE);
		AppendStat(TEXT("ATTACK_SPEED"), ATTACK_SPEED);
		AppendStat(TEXT("MOVE_SPEED"), MOVE_SPEED);
		AppendStat(TEXT("LIFE_STEAL"), LIFE_STEAL);
		AppendStat(TEXT("CRITICAL_CHANCE"), CRITICAL_CHANCE);
		AppendStat(TEXT("CRITICAL_DAMAGE"), CRITICAL_DAMAGE);
		AppendStat(TEXT("AVOID"), AVOID);
		AppendStat(TEXT("COOLDOWN_REDUCTION"), COOLDOWN_REDUCTION);

		return StatString;
	}

	// operator+ 구현
	FTotalStatus operator+(const FTotalStatus& Other) const
	{
		FTotalStatus Result;
		Result.HP = HP + Other.HP;
		Result.HP_ABSORB = HP_ABSORB + Other.HP_ABSORB;
		Result.MP = MP + Other.MP;
		Result.MP_ABSORB = MP_ABSORB + Other.MP_ABSORB;
		Result.STRENGTH = STRENGTH + Other.STRENGTH;
		Result.AGILITY = AGILITY + Other.AGILITY;
		Result.INTELLIGENCE = INTELLIGENCE + Other.INTELLIGENCE;
		Result.MAX_HP = MAX_HP + Other.MAX_HP;
		Result.MAX_MP = MAX_MP + Other.MAX_MP;
		Result.ATTACK = ATTACK + Other.ATTACK;
		Result.DEFENCE = DEFENCE + Other.DEFENCE;
		Result.ATTACK_SPEED = ATTACK_SPEED + Other.ATTACK_SPEED;
		Result.MOVE_SPEED = MOVE_SPEED + Other.MOVE_SPEED;
		Result.LIFE_STEAL = LIFE_STEAL + Other.LIFE_STEAL;
		Result.CRITICAL_CHANCE = CRITICAL_CHANCE + Other.CRITICAL_CHANCE;
		Result.CRITICAL_DAMAGE = CRITICAL_DAMAGE + Other.CRITICAL_DAMAGE;
		Result.AVOID = AVOID + Other.AVOID;
		Result.COOLDOWN_REDUCTION = COOLDOWN_REDUCTION + Other.COOLDOWN_REDUCTION;
		return Result;
	}
};

/*
	재능 정보
*/
USTRUCT(Atomic, BlueprintType)
struct FTalent
{
	GENERATED_BODY()

	TArray<TTuple<int32, int32>> Talents;

	void MakeTalent(Protocol::Talent Data);

	FString toString()
	{
		FString talentString;

		auto AppendTalent = [&talentString](int32 talent, int32 talentLevel)
			{
				if (!talentString.IsEmpty())
				{
					talentString.Append(TEXT(" "));
				}

				talentString.Append(FString::Printf(TEXT("%d = %d"), talent, talentLevel));
			};

		for (int i = 0; i < Talents.Num(); i++)
		{
			AppendTalent(Talents[i].Key, Talents[i].Value);
		}

		return talentString;
	}
};


USTRUCT(Atomic, BlueprintType)
struct FUserCharacter
{
	GENERATED_BODY()

	//유저 캐릭터
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserSeq = -1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString NickName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 NobilityRank;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TEnumAsByte<ECharacterMainJobType> MainJob;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TEnumAsByte<ECharacterSubJobType> SubJob;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 Exp;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 AdventureRank;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FTotalStatus TotalStatus;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FSetStatus SetStatus;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FTalent Talent;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector Transform;
	void MakeUserCharacter(Protocol::UserCharacter Data);

	/*임시 및 테스트 용*/
	Protocol::UserCharacter UserCharacterData;

	Protocol::UserCharacter& GetUserCharacterData() { return UserCharacterData; }
	void SetUserChracterData(Protocol::UserCharacter Value) { UserCharacterData = Value; }
};

USTRUCT(BlueprintType)
struct FPlayerMap
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<int32, FUserCharacter> PlayerMap;

	FUserCharacter& Add(int32 key, FUserCharacter value)
	{
		return PlayerMap.Add(key, value);
	}
};

