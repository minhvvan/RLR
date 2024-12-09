// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


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

//Monster
struct FMonsterStatus;

//util
struct FAttackResult;
struct FMoveResult;
struct FResourceData;
struct FClassData;
struct FEffectData;
struct FActionResult;

enum class EUIType : uint8;
enum class ESlotType : uint8;



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


