// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Network/Struct.pb.h>
#include "RLRStruct.generated.h"

/**
 * 
 */

 #define FLOAT_TO_FTEXT(floatValue) FText::FromString(FString::SanitizeFloat(floatValue))
#define INT_TO_FTEXT(Value) FText::FromString(FString::FromInt(Value))
 
UENUM(BlueprintType)
enum class EItemType : uint8
{
	EQUIPMENT,
	CONSUMPTION,
	ETC,
	NONE,
};


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

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	//무기, 방어구
	WEAPON,
	SUBWEAPON,
	HELMET,
	UPPERBODYARMOR,
	LOWERBODYARMOR,
	SHOES,
	GLOVES,
	//장신구

	NECKLACE,
	EARRING,
	RING,
	BRACELET,
	NONE,
};


UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	COMMON,
	UNCOMMON,
	RARE,
	UNIQUE,
	EPIC,
	LEGEND,
	NONE,
};


UENUM(BlueprintType)
enum class EUIType : uint8
{
	INVENTORY,
	CHARACTERSTAT,
	ITEMINFO,
	SIZE,
};


USTRUCT(Atomic, BlueprintType)
struct FStatus
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
	float HEALTH = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MAGIC = 0;

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
	float EVASION = 0;

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


	FString ToString() const
	{
		FString ItemString;

		auto AppendStat = [&ItemString](const FString& StatName, float StatValue)
			{
				if (StatValue != 0)
				{
					if (!ItemString.IsEmpty())
					{
						ItemString.Append(TEXT("\n"));
					}
					ItemString.Append(FString::Printf(TEXT("%s = %.2f"), *StatName, StatValue));
				}
			};

		AppendStat(TEXT("HP"), HP);
		AppendStat(TEXT("HP_ABSORB"), HP_ABSORB);
		AppendStat(TEXT("MP"), MP);
		AppendStat(TEXT("MP_ABSORB"), MP_ABSORB);
		AppendStat(TEXT("HEALTH"), HEALTH);
		AppendStat(TEXT("MAGIC"), MAGIC);
		AppendStat(TEXT("STRENGTH"), STRENGTH);
		AppendStat(TEXT("AGILITY"), AGILITY);
		AppendStat(TEXT("INTELLIGENCE"), INTELLIGENCE);
		AppendStat(TEXT("MAX_HP"), MAX_HP);
		AppendStat(TEXT("MAX_MP"), MAX_MP);
		AppendStat(TEXT("ATTACK"), ATTACK);
		AppendStat(TEXT("DEFENCE"), DEFENCE);
		AppendStat(TEXT("ATTACK_SPEED"), ATTACK_SPEED);
		AppendStat(TEXT("MOVE_SPEED"), MOVE_SPEED);
		AppendStat(TEXT("EVASION"), EVASION);
		AppendStat(TEXT("LIFE_STEAL"), LIFE_STEAL);
		AppendStat(TEXT("CRITICAL_CHANCE"), CRITICAL_CHANCE);
		AppendStat(TEXT("CRITICAL_DAMAGE"), CRITICAL_DAMAGE);
		AppendStat(TEXT("AVOID"), AVOID);
		AppendStat(TEXT("COOLDOWN_REDUCTION"), COOLDOWN_REDUCTION);

		return ItemString;
	}
};


/*
	아이템 정보를 위한 Status.
*/
USTRUCT(Atomic, BlueprintType)
struct FItemStatus
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
	float HEALTH = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MAGIC = 0;

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
	float EVASION = 0;

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

	FString ToString() const
	{
		FString ItemString;

		auto AppendStat = [&ItemString](const FString& StatName, float StatValue)
			{
				if (StatValue != 0)
				{
					if (!ItemString.IsEmpty())
					{
						ItemString.Append(TEXT("\n"));
					}
					ItemString.Append(FString::Printf(TEXT("%s = %.2f"), *StatName, StatValue));
				}
			};

		AppendStat(TEXT("HP"), HP);
		AppendStat(TEXT("HP_ABSORB"), HP_ABSORB);
		AppendStat(TEXT("MP"), MP);
		AppendStat(TEXT("MP_ABSORB"), MP_ABSORB);
		AppendStat(TEXT("HEALTH"), HEALTH);
		AppendStat(TEXT("MAGIC"), MAGIC);
		AppendStat(TEXT("STRENGTH"), STRENGTH);
		AppendStat(TEXT("AGILITY"), AGILITY);
		AppendStat(TEXT("INTELLIGENCE"), INTELLIGENCE);
		AppendStat(TEXT("MAX_HP"), MAX_HP);
		AppendStat(TEXT("MAX_MP"), MAX_MP);
		AppendStat(TEXT("ATTACK"), ATTACK);
		AppendStat(TEXT("DEFENCE"), DEFENCE);
		AppendStat(TEXT("ATTACK_SPEED"), ATTACK_SPEED);
		AppendStat(TEXT("MOVE_SPEED"), MOVE_SPEED);
		AppendStat(TEXT("EVASION"), EVASION);
		AppendStat(TEXT("LIFE_STEAL"), LIFE_STEAL);
		AppendStat(TEXT("CRITICAL_CHANCE"), CRITICAL_CHANCE);
		AppendStat(TEXT("CRITICAL_DAMAGE"), CRITICAL_DAMAGE);
		AppendStat(TEXT("AVOID"), AVOID);
		AppendStat(TEXT("COOLDOWN_REDUCTION"), COOLDOWN_REDUCTION);

		return ItemString;
	}
};


USTRUCT(Atomic, BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	//슬롯에 있는 아이템 데이터가 ITEM_ID == -1 이면 비어 있는 슬롯으로 처리 중.
	FItemData()
	{
		ITEM_ID = -1;
		ItemImage = nullptr;
		TYPE = EItemType::NONE;
		EQUIPMENT_TYPE = EEquipmentType::NONE;
		IsEquiped = false;
	}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 ITEM_SEQ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NAME;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECharacterMainJobType> MainJobType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECharacterSubJobType> SubJobType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemType> TYPE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EEquipmentType> EQUIPMENT_TYPE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemRarity> RANK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EQUIPMENT_LEVEL;


	/*
		나중에 FItemStatus로 바꿔줄 예정.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatus ITEM_STATUS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SALE_PRICE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 USE_PERIOD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TEXT;

	//아이템 리소스 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Model;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemImage;

	//DB에 저장되어야할 정보
	int32 ITEM_SLOT_IDX;
	int64 ITEM_ID;
	bool IsEquiped;

	//나중에 패킷 날라오면, 그 정보로 FItemData를 만들어준다.
	void MakeItemData(const Protocol::Item itemData);

	void SetItemSlotIndex(int32 Id){ITEM_SLOT_IDX = Id;}

	
};


UENUM(BlueprintType)
enum class ESkillType : uint8
{
	NORMAL = 0,
	AREA,
	HOLDING,
	SIZE
};


USTRUCT(Atomic, BlueprintType)
struct FSkillData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 SkillSeq;	
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 Level = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 Cost = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float CoolTime;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Cind;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 Duration;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float ActivityTime;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 SkillId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector CollisionRange;	
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	ESkillType SkillType;
};


USTRUCT(Atomic, BlueprintType)
struct FSkillClass : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 SkillSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<class UAction> SkillAnimClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<class UAction> SkillClass;
};


USTRUCT(Atomic, BlueprintType)
struct FAbnormal2
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Duration;
};

USTRUCT(Atomic, BlueprintType)
struct FMonsterStatus
{
	GENERATED_BODY()

	FMonsterStatus() :
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
	{}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 MonsterSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString MonsterName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 MonsterLevel;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 MontserExp;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 MonsterDamage;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 MonsterDefence;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 MonsterHp;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MonsterDistance;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MonsterTransX;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MonsterTransY;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MonsterTransZ;

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
		AppendStatInt(TEXT("Exp"), MontserExp);
		AppendStatInt(TEXT("Damage"), MonsterDamage);
		AppendStatInt(TEXT("Defence"), MonsterDefence);
		AppendStatFloat(TEXT("Distance"), MonsterDistance);
		AppendStatFloat(TEXT("X"), MonsterTransX);
		AppendStatFloat(TEXT("Y"), MonsterTransY);
		AppendStatFloat(TEXT("Z"), MonsterTransZ);
		AppendStatInt(TEXT("MapId"), MonsterMapId);

		return MonsterString;
	}

	//Test
	static int32 tempID;

	//TODO: 몬스터 정보 생성
	void MakeMonsterData(/*const Protocol::Item itemData*/);
};

USTRUCT(Atomic, BlueprintType)
struct FAttackResult
{
	GENERATED_BODY()

	FAttackResult() :
		SkillSeq(-1),
		Level(0),
		Timestamp(0),
		UserSeq(0)
	{}

	UPROPERTY(EditAnyWhere)
	int32 SkillSeq;

	UPROPERTY(EditAnyWhere)
	int32 Level;

	UPROPERTY(EditAnyWhere)
	uint64 Timestamp;

	UPROPERTY(EditAnyWhere)
	uint32 UserSeq;

	UPROPERTY(EditAnyWhere)
	TArray<uint32> TargetSeq;

	FString ToString() const
	{
		FString AttackString;

		auto AppendStatInt = [&AttackString](const FString& StatName, float StatValue)
			{
				if (!AttackString.IsEmpty()) AttackString.Append(TEXT("\n"));
				AttackString.Append(FString::Printf(TEXT("%s = %.2f"), *StatName, StatValue));
			};

		AppendStatInt(TEXT("SkillSEQ"), SkillSeq);
		AppendStatInt(TEXT("Level"), Level);
		AppendStatInt(TEXT("Timestamp"), Timestamp);
		AppendStatInt(TEXT("UserSeq"), UserSeq);
		for (auto target : TargetSeq)
		{
			AppendStatInt(TEXT("Target"), target);
		}

		return AttackString;
	}

	void MakeAttackData(/*const Protocol::Item itemData*/);
};