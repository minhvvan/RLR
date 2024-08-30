// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/RLRStruct.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"

#include "Structs/PlayerStructs.h"
#include "Structs/ItemStructs.h"

#include "Network/Proto/Packet.pb.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

const FMonsterStatus FMonsterStatus::EmptyMonsterData;


void FMonsterStatus::MakeMonsterData(const Protocol::Monster monsterData)
{
    //(X=1250.000000,Y=1930.000000,Z=96.000000)
    MonsterSeq = monsterData.monsterseq();
    MonsterName = UTF8_TO_TCHAR(monsterData.monstername().c_str());
    MonsterLevel = monsterData.monsterlevel();
    MonsterExp = monsterData.monsterexp();
    MonsterAttackRate = monsterData.monsterdamage();
    MonsterDefence = monsterData.monsterdefence();
    MonsterHp = monsterData.monsterhp();
    MonsterAttackRange = 10;  // Packet 추가 예정
    MonsterTransform = { monsterData.monstertransx(), monsterData.monstertransy(), monsterData.monstertransz() };
    MonsterId = monsterData.monsterid();
    MonsterMapId = monsterData.monstermapid();
}


/*
Enum 변환 관련된 건, 찾아보기 좋게 맨 아래에 배치.
*/

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


void FTalent::MakeTalent(Protocol::Talent Data)
{
    Talents.Add(TPair<int32,int32>(Data.firsttalent(), Data.firsttalent()));
    Talents.Add(TPair<int32,int32>(Data.secondtalent(), Data.secondlevel()));
    Talents.Add(TPair<int32,int32>(Data.thirdtalent(), Data.thirdlevel()));
}
void FQuest::MakeQuestData(const Protocol::Quest quest)
{
    //TODO: QuestData 생성
    QuestSeq = quest.questseq();
    NPCSeq = quest.npcseq();
    QuestTitle = UTF8_TO_TCHAR(quest.questtitle().c_str());
    QuestText = UTF8_TO_TCHAR(quest.questtext().c_str());
    QuestDescription = UTF8_TO_TCHAR(quest.questdescription().c_str());
    QuestKind = quest.questkind();
    IsProgress = false;
    IsClear = false;

   
    for (const auto& questReward : quest.rewardseqs()) {
        FString rewardKey = UTF8_TO_TCHAR(questReward.first.c_str());  // rewardSeqs의 key
        FObjectMap reward;
        for (const auto& rewardMap : questReward.second.values()) {
        
            // 맵에 추가
            reward.Add(rewardMap.first, rewardMap.second);
        }
        Rewards.Add(rewardKey, reward);
    }

    for (const auto& questNeed : quest.needseqs()) {
        FString needKey = UTF8_TO_TCHAR(questNeed.first.c_str());  // needSeqs의 key
        FObjectMap need;
        for (const auto& needMap : questNeed.second.values()) {

            // 맵에 추가
            need.Add(needMap.first, needMap.second);
        }
        Needs.Add(needKey, need);
    }
    //FPlayerGoods pGoods;
    //pGoods.MakePlayerGoods(quest.rewardplayergoods());
    //PlayerGoods = pGoods;

    //FUserGoods uGoods;  
    //uGoods.MakeUserGoods(quest.rewardusergoods());
    //UserGoods = uGoods;
}

void FNPCData::MakeNPCData(const Protocol::NPC npc)
{
    //TODO: NPCData 생성
    NPCSeq = npc.npcseq();
    NPCName = UTF8_TO_TCHAR(npc.npcname().c_str());
    NPCTalk = UTF8_TO_TCHAR(npc.npctalk().c_str());
    NPCType = npc.npctype();
    NPCConcept = UTF8_TO_TCHAR(npc.npcconcept().c_str());
    NPCTransform = FVector(npc.npctransform().x(), npc.npctransform().y(), npc.npctransform().z());
    MapId = npc.mapid();

    FQuest quest;
    for (auto&& npcQuest : npc.quests()) {
        quest.MakeQuestData(npcQuest);
        NPCQuests.Add(quest);
    }
    
}

int FInteractData::testID = 0;
void FInteractData::MakeObjectData()
{
    //TODO: ObjectData 생성
    InteractType = EInteractObjectType::LOGGING;
    ObjectTransform = FVector(1400.f, 1500.f + 500 * testID++, 96);
}
