// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/Proto/Struct.pb.h"
#include "Network/Proto/User_2.pb.h"
#include "Network/Proto/Player_2.pb.h"
#include "GameManager/LiteralManager.h"
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

		AppendStat(RLRLITERAL.TotalStatus_HP, HP);
		AppendStat(RLRLITERAL.TotalStatus_HP_Absorb, HP_ABSORB);
		AppendStat(RLRLITERAL.TotalStatus_MP, MP);
		AppendStat(RLRLITERAL.TotalStatus_MP_Absorb, MP_ABSORB);
		AppendStat(RLRLITERAL.TotalStatus_Strength, STRENGTH);
		AppendStat(RLRLITERAL.TotalStatus_Agility, AGILITY);
		AppendStat(RLRLITERAL.TotalStatus_Intelligence, INTELLIGENCE);
		AppendStat(RLRLITERAL.TotalStatus_MaxHP, MAX_HP);
		AppendStat(RLRLITERAL.TotalStatus_MaxMP, MAX_MP);
		AppendStat(RLRLITERAL.TotalStatus_Attack, ATTACK);
		AppendStat(RLRLITERAL.TotalStatus_Defence, DEFENCE);
		AppendStat(RLRLITERAL.TotalStatus_Attack_Speed, ATTACK_SPEED);
		AppendStat(RLRLITERAL.TotalStatus_Move_Speed, MOVE_SPEED);
		AppendStat(RLRLITERAL.TotalStatus_Life_Steal, LIFE_STEAL);
		AppendStat(RLRLITERAL.TotalStatus_Critical_Chance, CRITICAL_CHANCE);
		AppendStat(RLRLITERAL.TotalStatus_Critical_Damage, CRITICAL_DAMAGE);
		AppendStat(RLRLITERAL.TotalStatus_Avoid, AVOID);
		AppendStat(RLRLITERAL.TotalStatus_Cooldown_Reduction, COOLDOWN_REDUCTION);

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

