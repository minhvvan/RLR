// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Network/Proto/Struct.pb.h>
//#include <Network/Proto/Skill.pb.h>
//#include <Network/Proto/NPCStruct.pb.h>
//#include <Network/Proto/User_2.pb.h>
//#include <Network/Proto/Player_2.pb.h>
#include <Network/Proto/Drop.pb.h>
#include "Templates/Tuple.h"
#include "RLRStruct.generated.h"


#define FLOAT_TO_FTEXT(floatValue) FText::FromString(FString::SanitizeFloat(floatValue))
#define INT_TO_FTEXT(Value) FText::FromString(FString::FromInt(Value))
#define STRING_TO_FTEXT(String) FText::FromString(UTF8_TO_TCHAR(String));

//Etc
class UAction;

//Item
struct FDropItem;

//Skill
struct FSkillData;
struct FAbnormal;

enum class ESkillGroup : uint8;
enum class EAbnormalType : uint8;

//Player
struct FUserCharacter;
struct FTalent;
struct FTotalStatus;
struct FSetStatus;

enum class ECharacterMainJobType : uint8;
enum class ECharacterSubJobType : uint8;

//Item
struct FItemData;
struct FPlayerGoods;
struct FUserGoods;

enum class EItemType : uint8;
enum class EEquipmentType : uint8;
enum class EItemRarity : uint8;
enum class EStatusType : uint8;
enum class EConsumptionType : uint8;
enum class EETCType : uint8;
enum class EGoodsType : uint8;

//Object
struct FObjectMap;
struct FQuest;
struct FNPCData;
struct FInteractData;

enum class EInteractObjectType : uint8;




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
struct FSkillClass : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 SkillSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<UAction> SkillAnimClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<UAction> SkillClass;
};

/*
	데이터 테이블에서 사용할 래핑용 구조체.
*/

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
	static const FMonsterStatus EmptyMonsterData;

	/** Operators */

	FORCEINLINE bool operator==(FMonsterStatus const& Other) const
	{
		if (MonsterId != Other.MonsterId)
			return false;

		return true;
	}
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
