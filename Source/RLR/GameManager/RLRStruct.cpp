// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/RLRStruct.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/LiteralManager.h"

#include "Structs/PlayerStructs.h"
#include "Structs/ItemStructs.h"

#include "Network/Proto/Packet.pb.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"


// 문자열을 EItemRarity으로 변환하는 함수
EItemRarity StringToEItemRarity(const FString& RarityString)
{
    if (RarityString.Equals(RLRLITERAL.ItemRarity_Common, ESearchCase::IgnoreCase))
    {
        return EItemRarity::COMMON;
    }
    else if (RarityString.Equals(RLRLITERAL.ItemRarity_Uncommon, ESearchCase::IgnoreCase))
    {
        return EItemRarity::UNCOMMON;
    }
    else if (RarityString.Equals(RLRLITERAL.ItemRarity_Rare, ESearchCase::IgnoreCase))
    {
        return EItemRarity::RARE;
    }
    else if (RarityString.Equals(RLRLITERAL.ItemRarity_Unique, ESearchCase::IgnoreCase))
    {
        return EItemRarity::UNIQUE;
    }
    else if (RarityString.Equals(RLRLITERAL.ItemRarity_Epic, ESearchCase::IgnoreCase))
    {
        return EItemRarity::EPIC;
    }
    else if (RarityString.Equals(RLRLITERAL.ItemRarity_Legend, ESearchCase::IgnoreCase))
    {
        return EItemRarity::LEGEND;
    }
    else if (RarityString.Equals(RLRLITERAL.ItemRarity_None, ESearchCase::IgnoreCase))
    {
        return EItemRarity::NONE;
    }
    else
    {
        // 잘못된 문자열 입력 처리, 예: 디폴트 값 반환 또는 에러 처리
        return EItemRarity::NONE; // 기본값을 NONE으로 설정
    }
}


EItemType StringToEItemType(const FString& ItemTypeString)
{
    if (ItemTypeString.Equals(RLRLITERAL.ItemType_Equipment, ESearchCase::IgnoreCase))
    {
        return EItemType::EQUIPMENT;
    }
    else if (ItemTypeString.Equals(RLRLITERAL.ItemType_Consumption, ESearchCase::IgnoreCase))
    {
        return EItemType::CONSUMPTION;
    }
    else if (ItemTypeString.Equals(RLRLITERAL.ItemType_Etc, ESearchCase::IgnoreCase))
    {
        return EItemType::ETC;
    }
    else if (ItemTypeString.Equals(RLRLITERAL.ItemType_None, ESearchCase::IgnoreCase))
    {
        return EItemType::NONE;
    }
    else
    {
        return EItemType::NONE; // 기본값
    }
}


ECharacterMainJobType StringToECharacterMainJobType(const FString& MainJobTypeString)
{
    if (MainJobTypeString.Equals(RLRLITERAL.CharacterMainJobType_Swordsman, ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::SWORDSMAN;
    }
    else if (MainJobTypeString.Equals(RLRLITERAL.CharacterMainJobType_Thief, ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::THEIF;
    }
    else if (MainJobTypeString.Equals(RLRLITERAL.CharacterMainJobType_Mage, ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::MAGE;
    }
    else if (MainJobTypeString.Equals(RLRLITERAL.CharacterMainJobType_Archer, ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::ARCHER;
    }
    else if (MainJobTypeString.Equals(RLRLITERAL.CharacterMainJobType_Priest, ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::PRIEST;
    }
    else if (MainJobTypeString.Equals(RLRLITERAL.CharacterMainJobType_None, ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::NONE;
    }
    else
    {
        return ECharacterMainJobType::NONE; // 기본값
    }
}

ECharacterSubJobType StringToECharacterSubJobType(const FString& SubJobTypeString)
{
    if (SubJobTypeString.Equals(RLRLITERAL.CharacterSubJobType_None, ESearchCase::IgnoreCase))
    {
        return ECharacterSubJobType::NONE;
    }
    else
    {
        return ECharacterSubJobType::NONE; // 기본값
    }
}

EEquipmentType StringToEEquipmentType(const FString& EquipmentTypeString)
{
    if (EquipmentTypeString.Equals(RLRLITERAL.EquipmentType_Weapon, ESearchCase::IgnoreCase))
    {
        return EEquipmentType::WEAPON;
    }
    else if (EquipmentTypeString.Equals(RLRLITERAL.EquipmentType_SubWeapon, ESearchCase::IgnoreCase))
    {
        return EEquipmentType::SUBWEAPON;
    }
    else if (EquipmentTypeString.Equals(RLRLITERAL.EquipmentType_Helmet, ESearchCase::IgnoreCase))
    {
        return EEquipmentType::HELMET;
    }
    else if (EquipmentTypeString.Equals(RLRLITERAL.EquipmentType_UpperbodyArmor, ESearchCase::IgnoreCase))
    {
        return EEquipmentType::UPPERBODYARMOR;
    }
    else if (EquipmentTypeString.Equals(RLRLITERAL.EquipmentType_LowerboddyArmor, ESearchCase::IgnoreCase))
    {
        return EEquipmentType::LOWERBODYARMOR;
    }
    else if (EquipmentTypeString.Equals(RLRLITERAL.EquipmentType_Shoes, ESearchCase::IgnoreCase))
    {
        return EEquipmentType::SHOES;
    }
    else if (EquipmentTypeString.Equals(RLRLITERAL.EquipmentType_Gloves, ESearchCase::IgnoreCase))
    {
        return EEquipmentType::GLOVES;
    }
    else if (EquipmentTypeString.Equals(RLRLITERAL.EquipmentType_Necklace, ESearchCase::IgnoreCase))
    {
        return EEquipmentType::NECKLACE;
    }
    else if (EquipmentTypeString.Equals(RLRLITERAL.EquipmentType_Earring, ESearchCase::IgnoreCase))
    {
        return EEquipmentType::EARRING;
    }
    else if (EquipmentTypeString.Equals(RLRLITERAL.EquipmentType_Ring, ESearchCase::IgnoreCase))
    {
        return EEquipmentType::RING;
    }
    else if (EquipmentTypeString.Equals(RLRLITERAL.EquipmentType_Bracelet, ESearchCase::IgnoreCase))
    {
        return EEquipmentType::BRACELET;
    }
    else if (EquipmentTypeString.Equals(RLRLITERAL.EquipmentType_None, ESearchCase::IgnoreCase))
    {
        return EEquipmentType::NONE;
    }
    else
    {
        return EEquipmentType::NONE; // 기본값
    }
}



// EItemType을 문자열로 변환하는 함수
FString EItemTypeToString(EItemType ItemType)
{
    uint8 Index = static_cast<uint8>(ItemType);
    if (Index < UE_ARRAY_COUNT(EItemTypeStrings))
    {
        return EItemTypeStrings[Index];
    }
    return TEXT("UNKNOWN"); // 알 수 없는 값 처리
}

// ECharacterMainJobType을 문자열로 변환하는 함수
FString ECharacterMainJobTypeToString(ECharacterMainJobType MainJobType)
{
    uint8 Index = static_cast<uint8>(MainJobType);
    if (Index < UE_ARRAY_COUNT(ECharacterMainJobTypeStrings))
    {
        return ECharacterMainJobTypeStrings[Index];
    }
    return TEXT("UNKNOWN"); // 알 수 없는 값 처리
}

// ECharacterSubJobType을 문자열로 변환하는 함수
FString ECharacterSubJobTypeToString(ECharacterSubJobType SubJobType)
{
    uint8 Index = static_cast<uint8>(SubJobType);
    if (Index < UE_ARRAY_COUNT(ECharacterSubJobTypeStrings))
    {
        return ECharacterSubJobTypeStrings[Index];
    }
    return TEXT("UNKNOWN"); // 알 수 없는 값 처리
}

// EEquipmentType을 문자열로 변환하는 함수
FString EEquipmentTypeToString(EEquipmentType EquipmentType)
{
    uint8 Index = static_cast<uint8>(EquipmentType);
    if (Index < UE_ARRAY_COUNT(EEquipmentTypeStrings))
    {
        return EEquipmentTypeStrings[Index];
    }
    return TEXT("UNKNOWN"); // 알 수 없는 값 처리
}

// EItemRarity을 문자열로 변환하는 함수
FString EItemRarityToString(EItemRarity ItemRarity)
{
    uint8 Index = static_cast<uint8>(ItemRarity);
    if (Index < UE_ARRAY_COUNT(EItemRarityStrings))
    {
        return EItemRarityStrings[Index];
    }
    return TEXT("UNKNOWN"); // 알 수 없는 값 처리
}

// EStatusType을 문자열로 변환하는 함수
FString EStatusTypeToString(EStatusType StatusType)
{
    uint8 Index = static_cast<uint8>(StatusType);
    if (Index < UE_ARRAY_COUNT(EStatusTypeStrings))
    {
        return EStatusTypeStrings[Index];
    }
    return TEXT("UNKNOWN"); // 알 수 없는 값 처리
}

FString ESkillGroupToString(ESkillGroup SkillGroup)
{
    uint8 Index = static_cast<uint8>(SkillGroup);
    if (Index < UE_ARRAY_COUNT(ESkillGroups))
    {
        return ESkillGroups[Index];
    }
    return TEXT("UNKNOWN"); // 알 수 없는 값 처리
}
