// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/RLRStruct.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"

#include "Structs/PlayerStructs.h"
#include "Structs/ItemStructs.h"

#include "Network/Proto/Packet.pb.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"


// 문자열을 EItemRarity으로 변환하는 함수
EItemRarity StringToEItemRarity(const FString& RarityString)
{
    if (RarityString.Equals(TEXT("COMMON"), ESearchCase::IgnoreCase))
    {
        return EItemRarity::COMMON;
    }
    else if (RarityString.Equals(TEXT("UNCOMMON"), ESearchCase::IgnoreCase))
    {
        return EItemRarity::UNCOMMON;
    }
    else if (RarityString.Equals(TEXT("RARE"), ESearchCase::IgnoreCase))
    {
        return EItemRarity::RARE;
    }
    else if (RarityString.Equals(TEXT("UNIQUE"), ESearchCase::IgnoreCase))
    {
        return EItemRarity::UNIQUE;
    }
    else if (RarityString.Equals(TEXT("EPIC"), ESearchCase::IgnoreCase))
    {
        return EItemRarity::EPIC;
    }
    else if (RarityString.Equals(TEXT("LEGEND"), ESearchCase::IgnoreCase))
    {
        return EItemRarity::LEGEND;
    }
    else if (RarityString.Equals(TEXT("NONE"), ESearchCase::IgnoreCase))
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
    if (ItemTypeString.Equals(TEXT("EQUIPMENT"), ESearchCase::IgnoreCase))
    {
        return EItemType::EQUIPMENT;
    }
    else if (ItemTypeString.Equals(TEXT("CONSUMPTION"), ESearchCase::IgnoreCase))
    {
        return EItemType::CONSUMPTION;
    }
    else if (ItemTypeString.Equals(TEXT("ETC"), ESearchCase::IgnoreCase))
    {
        return EItemType::ETC;
    }
    else if (ItemTypeString.Equals(TEXT("NONE"), ESearchCase::IgnoreCase))
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
    if (MainJobTypeString.Equals(TEXT("SWORDSMAN"), ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::SWORDSMAN;
    }
    else if (MainJobTypeString.Equals(TEXT("THIEF"), ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::THEIF;
    }
    else if (MainJobTypeString.Equals(TEXT("MAGE"), ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::MAGE;
    }
    else if (MainJobTypeString.Equals(TEXT("ARCHER"), ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::ARCHER;
    }
    else if (MainJobTypeString.Equals(TEXT("PRIEST"), ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::PRIEST;
    }
    else if (MainJobTypeString.Equals(TEXT("NONE"), ESearchCase::IgnoreCase))
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
    if (SubJobTypeString.Equals(TEXT("NONE"), ESearchCase::IgnoreCase))
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
    if (EquipmentTypeString.Equals(TEXT("WEAPON"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::WEAPON;
    }
    else if (EquipmentTypeString.Equals(TEXT("SUBWEAPON"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::SUBWEAPON;
    }
    else if (EquipmentTypeString.Equals(TEXT("HELMET"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::HELMET;
    }
    else if (EquipmentTypeString.Equals(TEXT("UPPERBODYARMOR"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::UPPERBODYARMOR;
    }
    else if (EquipmentTypeString.Equals(TEXT("LOWERBODYARMOR"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::LOWERBODYARMOR;
    }
    else if (EquipmentTypeString.Equals(TEXT("SHOES"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::SHOES;
    }
    else if (EquipmentTypeString.Equals(TEXT("GLOVES"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::GLOVES;
    }
    else if (EquipmentTypeString.Equals(TEXT("NECKLACE"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::NECKLACE;
    }
    else if (EquipmentTypeString.Equals(TEXT("EARRING"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::EARRING;
    }
    else if (EquipmentTypeString.Equals(TEXT("RING"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::RING;
    }
    else if (EquipmentTypeString.Equals(TEXT("BRACELET"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::BRACELET;
    }
    else if (EquipmentTypeString.Equals(TEXT("NONE"), ESearchCase::IgnoreCase))
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



void FAttackResult::MakeAttackData()
{
}


