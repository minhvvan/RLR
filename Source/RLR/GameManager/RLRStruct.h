// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Network/Proto/Struct.pb.h>
#include <Network/Proto/Skill.pb.h>
#include <Network/Proto/NPCStruct.pb.h>
#include <Network/Proto/User_2.pb.h>
#include <Network/Proto/Player_2.pb.h>
#include "Templates/Tuple.h"
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
enum class EStatusType : uint8
{
	HP,
	MP,
	STR,
	AGI,
	INT,
	NONE,
};

UENUM(BlueprintType)
enum class EConsumptionType : uint8
{
	/*
		프로토에도 딱히 정보 없어서 일단 만들어만 둠.
		
	*/

	COMMON,
	POTION,
	NONE,
};

UENUM(BlueprintType)
enum class EETCType : uint8
{
	NORMAL,
	QUEST,
	NONE,
};


UENUM(BlueprintType)
enum class EUIType : uint8
{
	INVENTORY,
	CHARACTERSTAT,
	CHATOPTION,
	ITEMINFOMATION,
	MINIMAP,
	STATUSDISPLAY,
	INGAMEMENU,
	PARTY,
	KEYOPTION,
	SKILL,
	SKILL_UPGRADE,
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
		ITEM_SEQ = -1;
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
	FTotalStatus ITEM_STATUS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SALE_PRICE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 USE_PERIOD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TEXT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ITEM_VALUE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ITEM_MAX;
	/*
		Consumption
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float COOLDOWN;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CONSUMPTION_VALUE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CONSUMPTION_DURATION ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EStatusType> CONSUMPTION_STATUS_TYPE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EConsumptionType> CONSUMPTION_TYPE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EETCType> ETC_TYPE;

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
	Protocol::Item MakeItemPacket();
	static const FItemData EmptyItemData;

	void SetItemSlotIndex(int32 Id){ITEM_SLOT_IDX = Id;}

	/** Operators */
	FORCEINLINE bool operator==(FItemData const& Other) const
	{
		if (ITEM_SEQ != Other.ITEM_SEQ)
			return false;
		return true;
	}
};

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	NORMAL = 0,
	AREA,
	HOLDING,
	SIZE
};

UENUM(BlueprintType)
enum class EInteractObjectType : uint8
{
	COLLECT = 0,
	MINING,
	LOGGING,
	FISHING,
	SWIMMING,
	NONE
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
enum  class ESkillGroup : uint8
{
	NORMAL =	 0,		//일반
	UNIQUE,					//고유
	ULTIMATE,				//각성기
	NONE,
};


USTRUCT(Atomic, BlueprintType)
struct FSkillData : public FTableRowBase
{
	GENERATED_BODY()

	FSkillData (){};

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 SkillSeq = -1;	
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterMainJobType MainJobType = ECharacterMainJobType::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillGroup SkillGroup = ESkillGroup::NONE;

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

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> SkillImage;

	/*
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		스킬 미리보기 
	*/

	void MakeSkillData(Protocol::SkillInfo skill);
	static const FSkillData EmptySkillData;

	/** Operators */
	FORCEINLINE bool operator==(FSkillData const& Other) const
	{
		if(SkillId != Other.SkillId)
			return false;

		if(SkillSeq != Other.SkillSeq)
			return false;

		return true;
	}

	FString ToString() const;
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

/*
	데이터 테이블에서 사용할 래핑용 구조체.
*/
 USTRUCT(BlueprintType)
struct FSkillList
{
	 GENERATED_BODY()
	 UPROPERTY()
	TMap<int32, FSkillData> SkillList;
};

USTRUCT(Atomic, BlueprintType)
struct FAbnormal2
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
		MonsterTransform({0.f, 0.f, 0.f}),
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

	//Test
	static int32 tempID;

	void MakeMonsterData(const Protocol::Monster monsterData);
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

USTRUCT(Atomic, BlueprintType)
struct FUserCharacter
{
	GENERATED_BODY()

	//유저 캐릭터
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserSeq = -1; 

	//플레이어 == 클라이언트
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 PlayerSeq = -1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 MapId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 ChannelId;

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

	void MakeUserCharacter(Protocol::UserCharacter Data);

	/*임시 및 테스트 용*/
	Protocol::UserCharacter UserCharacterData;

	Protocol::UserCharacter&	GetUserCharacterData(){return UserCharacterData;}
	void SetUserChracterData(Protocol::UserCharacter Value) {UserCharacterData = Value;}
};

USTRUCT(Atomic, BlueprintType)
struct FMoveResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 MapId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 ChannelId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector TargetTransform;
};

USTRUCT(Atomic, BlueprintType)
struct FExpTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 MaxExp;
};

USTRUCT(Atomic, BlueprintType)
struct FResourceData : public FTableRowBase
{
	GENERATED_BODY()
	int32 ResourceID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;
};


/*

	작업을 하다보면 각종 Class 정보들을 로드해야 한다.
	그런데 하드 코딩으로 파일 주소를 불러와서 정보를 로드하는 건 조금 그러니.
	데이터 테이블을 만들어서 파일을 관리하기 위한 용도.

	테이블의 행 이름은 왠만해선 블루프린트 이름 그대로 해주자.

*/
USTRUCT(Atomic, BlueprintType)
struct FClassData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UObject> RLRClass;

	//무슨 용도로 쓰는지 메모용.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DataInfo;
};



/*
	Enum 변환 관련된 건, 찾아보기 좋게 맨 아래에 배치.
*/

// 문자열 배열 정의
const FString EItemTypeStrings[] = {
	TEXT("UNKNOWN"), // 0, 사용되지 않음
	TEXT("EQUIPMENT"), // 1
	TEXT("CONSUMPTION"), // 2
	TEXT("ETC"), // 3
	TEXT("UNKNOWN"), // 4
	TEXT("UNKNOWN"), // 5
	TEXT("UNKNOWN"), // 6
	TEXT("UNKNOWN"), // 7
	TEXT("UNKNOWN"), // 8
	TEXT("NONE") // 9
};

const FString ECharacterMainJobTypeStrings[] = {
	TEXT("SWORDSMAN"),
	TEXT("THEIF"),
	TEXT("MAGE"),
	TEXT("ARCHER"),
	TEXT("PRIEST"),
	TEXT("NONE")
};

const FString ECharacterSubJobTypeStrings[] = {
	TEXT("NONE")
};

const FString EEquipmentTypeStrings[] = {
	TEXT("WEAPON"),
	TEXT("SUBWEAPON"),
	TEXT("HELMET"),
	TEXT("UPPERBODYARMOR"),
	TEXT("LOWERBODYARMOR"),
	TEXT("SHOES"),
	TEXT("GLOVES"),
	TEXT("NECKLACE"),
	TEXT("EARRING"),
	TEXT("RING"),
	TEXT("BRACELET"),
	TEXT("NONE")
};

const FString EItemRarityStrings[] = {
	TEXT("COMMON"),
	TEXT("UNCOMMON"),
	TEXT("RARE"),
	TEXT("UNIQUE"),
	TEXT("EPIC"),
	TEXT("LEGEND"),
	TEXT("NONE")
};

// 문자열 배열 정의
const FString EStatusTypeStrings[] = {
	TEXT("COMMON"),
	TEXT("UNCOMMON"),
	TEXT("RARE"),
	TEXT("UNIQUE"),
	TEXT("EPIC"),
	TEXT("LEGEND"),
	TEXT("NONE"),
};


const FString ESkillGroups[] = {
	TEXT("NORMAL"),
	TEXT("UNIQUE"),
	TEXT("ULTIMATE"),
	TEXT("NONE"),
};

EItemType StringToEItemType(const FString& ItemTypeString);
ECharacterMainJobType StringToECharacterMainJobType(const FString& MainJobTypeString);
ECharacterSubJobType StringToECharacterSubJobType(const FString& SubJobTypeString);
EEquipmentType StringToEEquipmentType(const FString& EquipmentTypeString);
EItemRarity StringToEItemRarity(const FString& RarityString);

FString EItemTypeToString(EItemType ItemType);
FString ECharacterMainJobTypeToString(ECharacterMainJobType MainJobType);
FString ECharacterSubJobTypeToString(ECharacterSubJobType SubJobType);
FString EEquipmentTypeToString(EEquipmentType EquipmentType);
FString EStatusTypeToString(EStatusType StatusType);
FString ESkillGroupToString(ESkillGroup SkillGroup);

USTRUCT(Atomic, BlueprintType)
struct FPlayerGoods
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int TotalMoney;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int Diamond;

	FString ToString() const
	{
		FString PlayerGoodsString;

		auto AppendInt = [&PlayerGoodsString](const FString& StatName, int32 StatValue)
			{
				if (!PlayerGoodsString.IsEmpty()) PlayerGoodsString.Append(TEXT("\n"));
				PlayerGoodsString.Append(FString::Printf(TEXT("%s = %d"), *StatName, StatValue));
			};

		AppendInt(TEXT("TOTALMONEY"), TotalMoney);
		AppendInt(TEXT("DIAMOND"), Diamond);

		return PlayerGoodsString;
	}

	void MakePlayerGoods(const Protocol::PlayerGood playerGood);
};

USTRUCT(Atomic, BlueprintType)
struct FUserGoods
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int Reputation;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int Contribution;

	FString ToString() const
	{
		FString UserGoodsString;

		auto AppendInt = [&UserGoodsString](const FString& StatName, int32 StatValue)
			{
				if (!UserGoodsString.IsEmpty()) UserGoodsString.Append(TEXT("\n"));
				UserGoodsString.Append(FString::Printf(TEXT("%s = %d"), *StatName, StatValue));
			};

		AppendInt(TEXT("REPUTATION"), Reputation);
		AppendInt(TEXT("CONTRIBUTION"), Contribution);

		return UserGoodsString;
	}

	void MakeUserGoods(const Protocol::UserGood userGood);
};


USTRUCT(Atomic, BlueprintType)
struct FObjectMap
{
	GENERATED_BODY()
	TMap<int, int> Map;

	FString ToString() const
	{
		FString OutString;

		auto AppendStatInt = [&OutString](int key, int value)
			{
				if (!OutString.IsEmpty()) OutString.Append(TEXT(", "));
				OutString.Append(FString::Printf(TEXT("{%d:%d}"), key, value));
			};
		
		for (const auto& [seq, amount] : Map)
		{
			AppendStatInt(seq, amount);
		}

		return OutString;
	}

	void Add(int key, int value)
	{
		Map.Add(key, value);
	}
};


USTRUCT(Atomic, BlueprintType)
struct FQuest
{
	GENERATED_BODY()

	FQuest()
	{}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int QuestSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int NPCSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString QuestTitle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString QuestText;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString QuestDescription;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int QuestKind;	
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool IsProgress;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool IsClear;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TMap<FString, FObjectMap> Rewards;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TMap<FString, FObjectMap> Needs;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FPlayerGoods PlayerGoods;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FUserGoods UserGoods;

	FString ToString() const
	{
		FString QuestString;

		auto AppendQuestInt = [&QuestString](const FString& StatName, int32 StatValue)
			{
				if (!QuestString.IsEmpty()) QuestString.Append(TEXT("\n"));
				QuestString.Append(FString::Printf(TEXT("%s = %d"), *StatName, StatValue));
			};

		auto AppendQuestString = [&QuestString](const FString& StatName, FString StatValue)
			{
				if (!QuestString.IsEmpty()) QuestString.Append(TEXT("\n"));
				QuestString.Append(FString::Printf(TEXT("%s = %s"), *StatName, *StatValue));
			};

		auto AppendQuestBool = [&QuestString](const FString& StatName, bool StatValue)
			{
				if (!QuestString.IsEmpty()) QuestString.Append(TEXT("\n"));
				FString str = StatValue ? TEXT("TRUE") : TEXT("FALSE");
				QuestString.Append(FString::Printf(TEXT("%s = %s"), *StatName, *str));
			};

		AppendQuestInt(TEXT("SEQ"), QuestSeq);
		AppendQuestInt(TEXT("NPCSEQ"), NPCSeq);
		AppendQuestString(TEXT("QUESTTITLE"), QuestTitle);
		AppendQuestString(TEXT("QUESTTEXT"), QuestText);
		AppendQuestString(TEXT("QUESTDECRIPTION"), QuestDescription);
		AppendQuestInt(TEXT("QUESTKIND"), QuestKind);
		AppendQuestBool(TEXT("ISPROGRESS"), IsProgress);
		AppendQuestBool(TEXT("ISCLEAR"), IsClear);

		QuestString.Append(FString::Printf(TEXT("\n---------------\n")));
		QuestString.Append(FString::Printf(TEXT("\nREWARDS\n")));
		for (const auto& [type, rewards] : Rewards)
		{
			AppendQuestString(type, rewards.ToString());
		}

		QuestString.Append(FString::Printf(TEXT("\n---------------\n")));
		QuestString.Append(FString::Printf(TEXT("\nNEEDS\n")));
		for (const auto& [type, need] : Needs)
		{
			AppendQuestString(type, need.ToString());
		}

		QuestString.Append(FString::Printf(TEXT("\nPLAYERGOODS\n")));
		QuestString.Append(PlayerGoods.ToString());
		QuestString.Append(FString::Printf(TEXT("\nUSERGOODS\n")));
		QuestString.Append(UserGoods.ToString());

		return QuestString;
	}

	void MakeQuestData(const Protocol::Quest quest);


};


USTRUCT(Atomic, BlueprintType)
struct FNPCData
{
	GENERATED_BODY()

	FNPCData():
		NPCTransform(FVector::ZeroVector)
	{}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int NPCSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString NPCName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString NPCTalk;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int NPCType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString NPCConcept;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector NPCTransform;	
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 MapId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<FQuest> NPCQuests;

	FString ToString() const
	{
		FString NPCString;

		auto AppendFloat = [&NPCString](const FString& StatName, float StatValue)
			{
				if (!NPCString.IsEmpty()) NPCString.Append(TEXT("\n"));
				NPCString.Append(FString::Printf(TEXT("%s = %.2f"), *StatName, StatValue));
			};

		auto AppendInt = [&NPCString](const FString& StatName, int32 StatValue)
			{
				if (!NPCString.IsEmpty()) NPCString.Append(TEXT("\n"));
				NPCString.Append(FString::Printf(TEXT("%s = %d"), *StatName, StatValue));
			};

		auto AppendString = [&NPCString](const FString& StatName, FString StatValue)
			{
				if (!NPCString.IsEmpty()) NPCString.Append(TEXT("\n"));
				NPCString.Append(FString::Printf(TEXT("%s = %s"), *StatName, *StatValue));
			};

		auto AppendVector = [&NPCString](const FString& StatName, FVector StatValue)
			{
				if (!NPCString.IsEmpty()) NPCString.Append(TEXT("\n"));
				NPCString.Append(FString::Printf(TEXT("%s = %s"), *StatName, *StatValue.ToString()));
			};

		AppendInt(TEXT("SEQ"), NPCSeq);
		AppendString(TEXT("NAME"), NPCName);
		AppendString(TEXT("TALK"), NPCTalk);
		AppendInt(TEXT("TYPE"), NPCType);
		AppendString(TEXT("CONCEPT"), NPCConcept);
		AppendVector(TEXT("TRANSFORM"), NPCTransform);
		AppendInt(TEXT("MAPID"), MapId);

		NPCString.Append(TEXT("\nQUESTS\n"));
		for (auto quest : NPCQuests)
		{
			NPCString.Append(TEXT("--------------\n"));
			NPCString.Append(quest.ToString());
			NPCString.Append(TEXT("\n--------------\n"));
		}

		return NPCString;
	}

	void MakeNPCData(const Protocol::NPC npc);


};

USTRUCT(Atomic, BlueprintType)
struct FInteractData
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	EInteractObjectType InteractType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector ObjectTransform;

	void MakeObjectData(/*param*/);
	//TODO:MakeData 구현 후 삭제
	static int testID;
};

USTRUCT(Atomic, BlueprintType)
struct FEffectData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite);
	int32 PlayerSkillSeq;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite);
	int32 MonsterSeq;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite);
	FVector HitTransform;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite);
	FString EffectPath;
};
