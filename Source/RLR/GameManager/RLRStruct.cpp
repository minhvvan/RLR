// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/RLRStruct.h"

#include "Network/Proto/Packet.pb.h"


void FStatus::MakeStatus(Protocol::UserTotalStatus Status)
{
    HP = Status.userhp();
    HP_ABSORB = Status.userhpabsorb();
    MP = Status.usermp();
	MP_ABSORB = Status.usermpabsorb();

    STRENGTH = Status.userstrength();
    AGILITY = Status.useragility();
    INTELLIGENCE = Status.userintelligence();

    MAX_HP = Status.usermaxhp();
    MAX_MP = Status.usermaxmp();

    ATTACK = Status.userattack();
    DEFENCE = Status.userdefence();
    ATTACK_SPEED = Status.userattackspeed();
    MOVE_SPEED = Status.usermovespeed();
    CRITICAL_CHANCE = Status.usercriticalchance();
    CRITICAL_DAMAGE = Status.usercriticaldamage();
    AVOID = Status.useravoid();
    COOLDOWN_REDUCTION = Status.usercooldownreduction();
}


void FItemData::MakeItemData(const Protocol::Item itemData)
{
    ITEM_SEQ = itemData.itemseq();
   ITEM_ID = itemData.itemid();
    ITEM_SLOT_IDX = itemData.itemslotidx();
    UE_LOG(LogTemp, Log, TEXT("ITEM_SEQ : %d"), ITEM_SEQ);
    UE_LOG(LogTemp, Log, TEXT("ITEM_ID : %lld"), itemData.itemid());
    UE_LOG(LogTemp, Log, TEXT("ITEM_SLOT_IDX : %d"), ITEM_SLOT_IDX);

	NAME = UTF8_TO_TCHAR(itemData.name().c_str());

    FString ItemType = UTF8_TO_TCHAR(itemData.type().c_str());
	TYPE = StringToEItemType(ItemType);

    /*Rank는 int 형?*/
	RANK = (EItemRarity) itemData.rank();
    EQUIPMENT_LEVEL = itemData.equiplevel();
	SALE_PRICE = itemData.saleprice();
	USE_PERIOD = itemData.useperiod();
	TEXT = UTF8_TO_TCHAR(itemData.text().c_str());

	ITEM_VALUE = itemData.itemvalue();
	ITEM_MAX = itemData.itemmax();
    
    if (itemData.has_equip()) {
        auto equipData = itemData.equip();

        ITEM_STATUS.HP = equipData.hp();
        ITEM_STATUS.HP_ABSORB = equipData.hpabsorb();
        ITEM_STATUS.MP = equipData.mp();
        ITEM_STATUS.MP_ABSORB = equipData.mpabsorb();
        ITEM_STATUS.STRENGTH = equipData.strength();
        ITEM_STATUS.AGILITY = equipData.agility();
        ITEM_STATUS.INTELLIGENCE = equipData.intelligence();
        ITEM_STATUS.ATTACK = equipData.attack();
        UE_LOG(LogTemp, Log, TEXT("itemData 공격력 : %f"), equipData.attack());
        ITEM_STATUS.DEFENCE = equipData.defence();
        ITEM_STATUS.ATTACK_SPEED = equipData.attackspeed();
        ITEM_STATUS.MOVE_SPEED = equipData.movespeed();
        ITEM_STATUS.CRITICAL_CHANCE = equipData.criticalchance();
        ITEM_STATUS.CRITICAL_DAMAGE = equipData.criticaldamage();
        ITEM_STATUS.AVOID = equipData.avoid();
        ITEM_STATUS.COOLDOWN_REDUCTION = equipData.cooldownreduction();
        EQUIPMENT_TYPE = (EEquipmentType) equipData.equippart();
    }

    if (itemData.has_consumption()) {
        auto consumptionData = itemData.consumption();
		COOLDOWN = consumptionData.cooldown();
		CONSUMPTION_VALUE = consumptionData.value();
		CONSUMPTION_DURATION = consumptionData.duration();
		CONSUMPTION_STATUS_TYPE = (EStatusType)consumptionData.statustype();
		CONSUMPTION_TYPE = (EConsumptionType)consumptionData.contype();
	}

    if (itemData.has_etcitem()) {
        auto etcItemData = itemData.etcitem();
        ETC_TYPE =  (EETCType)etcItemData.etctype();
    }
}



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

int32 FMonsterStatus::tempID = 0;
void FMonsterStatus::MakeMonsterData(const Protocol::Monster monsterData)
{
    //(X=1250.000000,Y=1930.000000,Z=96.000000)
    MonsterSeq = monsterData.monsterseq();
    MonsterName = UTF8_TO_TCHAR(monsterData.monstername().c_str());
    MonsterLevel = monsterData.monsterlevel();
    MontserExp = monsterData.monsterexp();
    MonsterDamage = monsterData.monsterdamage();
    MonsterDefence = monsterData.monsterdefence();
    MonsterHp = monsterData.monsterhp();
    MonsterDistance = 10;  // Packet 추가 예정
    MonsterTransX = monsterData.monstertransx();
    MonsterTransY = monsterData.monstertransy();
    MonsterTransZ = monsterData.monstertransz();
    MonsterId = monsterData.monsterid();
    MonsterMapId = monsterData.monstermapid();
}
void FMonsterStatus::UpdateTransform(float x, float y, float z) {
    MonsterTransX = x;
    MonsterTransY = y;
    MonsterTransZ = z;
}