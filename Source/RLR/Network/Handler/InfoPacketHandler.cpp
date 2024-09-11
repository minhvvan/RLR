// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/InfoPacketHandler.h"
#include <GameManager/RLRStruct.h>
#include "GameManager/GameManager.h"
#include "GameManager/MonsterManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/SkillManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/ObjectManager.h"
#include "GameManager/QuestManager.h"
#include "Structs/SkillStructs.h"
#include "Structs/PlayerStructs.h"
#include "Structs/ObjectStructs.h"
#include "Structs/MonsterStructs.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

bool Handle_MAP_INFO_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_MapMonsterInfoResponsePacket& pkt) {

    TArray< FMonsterStatus> monsterDatas;
    for (int i = 0; i < pkt.monsters_size(); i++) {
        FMonsterStatus monsterData;
        monsterData.MakeMonsterData(pkt.monsters().at(i));
        monsterDatas.Add(monsterData);

    }

    GameInstance->GetMonsterManager()->SetMonsterData(monsterDatas);



    return false;
}
bool Handle_INVENTORY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_InventoryResponsePacket& pkt)
{

    TArray<FItemData> itemDatas;
    for (int32 i = 0; i < pkt.items_size(); i++) {
        FItemData itemData;
        itemData.MakeItemData(pkt.items().at(i));

        itemDatas.Add(itemData);
    }

    GameInstance->GetInventoryManager()->GetItemList(itemDatas);


    return true;
}
bool Handle_STATUS_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_StatusResponsePacket& pkt) {

    UUIManager* UIManager = GameInstance->GetUIManager();
    
    //UE_LOG(LogTemp, Log, TEXT("User Hp : %f"), pkt.usercharacter().totalstatus().userhp());
    if (IsValid(UIManager) == false)
    {
        DEBUG_LOG("Handle_STATUS_RESPONSE Error. UIManager is Null.");
        return false;
    }

    FUserCharacter UserCharacter;
    UserCharacter.MakeUserCharacter(pkt.usercharacter());
    GameInstance->GetPlayerManager()->SetPlayerData(UserCharacter);

    //UIManager->UpdatedPlayerInfo.Broadcast(UserCharacter); 플레이어 매니저로 이전 
    return true;
}
bool Handle_USER_SPAWN_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_UserSpawnResponse& pkt) {

    FUserCharacter UserCharacter;
    UserCharacter.MakeUserCharacter(pkt.usercharacter());
    GameInstance->GetPlayerManager()->SetPlayerData(UserCharacter);
    GameInstance->GetPlayerManager()->UpdatePlayerTransform(FVector(pkt.usercharacter().transx(), pkt.usercharacter().transy(), pkt.usercharacter().transz()));
    GameInstance->GetNetworkManager()->SetMapId(pkt.usercharacter().mapid());
    GameInstance->GetNetworkManager()->SetUserSeq(pkt.usercharacter().userseq());
    //GameInstance->GetNetworkManager()->SendGetSkillPacket();
    GameInstance->GetNetworkManager()->SendNPCInfoPacket();
    // item 이미지 없어서 로드 안됌 로드 완료시 연결예정
    GameInstance->GetNetworkManager()->SendInventoryPacket();
    return true;
}
bool Handle_GET_SKILL_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GetSkillResponsePacket& pkt) {
    TArray<FSkillData> skillDatas;
    for (auto& skill : pkt.skill()) {
        FSkillData skillData;
        skillData.MakeSkillData(skill);

        skillDatas.Add(skillData);
    }
    GameInstance->GetSkillManager()->SetSelectedSkills(skillDatas);
    return true;
}


bool  Handle_CHANNEL_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_ChannelResponsePacket& pkt) {
    UE_LOG(LogTemp, Log, TEXT("User Channel : %d"), pkt.channelid());
    //TODO : PlayerManager or UserManager 만들면 거기에 Channel 정보도 같이 리스폰

    GameInstance->GetNetworkManager()->SendMapInfoRequest(pkt.channelid());
    return true;
}

bool Handle_NPC_INFO_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_NPCInfoResponse& pkt)
{
    //TODO : Object Manager 에 연결
    UE_LOG(LogTemp, Log, TEXT("NPc Spawn Start "));

    TArray<FNPCData> npcDatas;
    for (auto& npc : pkt.npc()) {
        FNPCData npcData;
        npcData.MakeNPCData(npc);

        npcDatas.Add(npcData);
    }

    GameInstance->GetObjectManager()->SetNPCData(npcDatas);



    return false;
}

bool Handle_USER_QUEST_INFO_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_UserQuestInfoResponse& pkt)
{
    TArray<FQuest> questDatas;
    for (auto& quest : pkt.quests()) {
        FQuest questData;
        questData.MakeQuestData(quest);
        questDatas.Add(questData);
    }

    //TODO : Player Manager 에 User 퀘스트의 연결
    //GameInstance->GetPlayerManager()->SetUserQuest(questDatas); 
    GameInstance->GetQuestManager()->SetUserQuests(questDatas);

    return false;
}

bool Handle_QUEST_ADD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_QuestAddResponse& pkt)
{
    // 오는게 true, false 밖에 없어서 따로 로직 구현 X
    return false;
}

bool Handle_QUEST_CHECK_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_QuestCheckResponse& pkt)
{
    // 오는게 true, false 밖에 없어서 따로 로직 구현 X
    return false;
}

bool Handle_QUEST_COMPLETE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_QuestCompleteResponse& pkt)
{
    // 오는게 true, false 밖에 없어서 따로 로직 구현 X
    // TODO : 플레이어 보상 지급, QuestListUI에서 완료한 퀘스트 버튼 삭제
    return false;
}

bool Handle_SHOP_BUY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_BuyResponse& pkt)
{
    // 오는게 true, false 밖에 없어서 따로 로직 구현 X
    return false;
}

bool Handle_SHOP_SELL_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_SellResponse& pkt)
{
    // 오는게 true, false 밖에 없어서 따로 로직 구현 X
    return false;
}

bool Handle_EXP_INCREASE_REPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_ExpIncreaseResponse& pkt)
{
    GameInstance->GetPlayerManager()->UpdatePlayerExp(pkt.exp());
    GameInstance->GetPlayerManager()->UpdatePlayerLevel(pkt.level());
    
   
    return false;
}

