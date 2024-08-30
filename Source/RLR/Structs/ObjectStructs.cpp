// Fill out your copyright notice in the Description page of Project Settings.


#include "Structs/ObjectStructs.h"
#include "Network/Proto/Packet.pb.h"
#include "GameManager/GameManager.h"
#include "GameManager/MonsterManager.h"

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

void FDropItem::MakeDropItemData(int64 objectId, int32 value, int64 monsterId)
{
    auto monsterManager = GameInstance->GetMonsterManager();
    if (!monsterManager) return;

    //TODO: Data채우기
    //Seq enum : EGoodsType
    ObjectTransform = monsterManager->GetMonsterTransformById(monsterId);
}