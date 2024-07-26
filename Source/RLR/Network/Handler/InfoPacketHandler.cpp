// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/InfoPacketHandler.h"
#include <GameManager/RLRStruct.h>
#include "GameManager/GameManager.h"
#include "GameManager/MonsterManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/SkillManager.h"
#include "GameManager/NetworkManager.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

bool Handle_MAP_INFO_REQUEST(TSharedPtr<PacketSession>& session, Protocol::MapMonsterInfoRequestPacket& pkt) {


    return false;
}
bool Handle_MAP_INFO_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::MapMonsterInfoResponsePacket& pkt) {

    TArray< FMonsterStatus> monsterDatas;
    for (int i = 0; i < pkt.monsters_size(); i++) {
        FMonsterStatus monsterData;
        monsterData.MakeMonsterData(pkt.monsters().at(i));
        monsterDatas.Add(monsterData);

    }

    GameInstance->GetMonsterManager()->SetMonsterData(monsterDatas);



    return false;
}
bool Handle_INVENTORY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::InventoryResponsePacket& pkt)
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
bool Handle_STATUS_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::StatusResponsePacket& pkt) {

    UE_LOG(LogTemp, Log, TEXT("User level : %d"), pkt.usercharacter().level());
    UE_LOG(LogTemp, Log, TEXT("User hp : %d"), pkt.usercharacter().setstatus().userhp());

    UUIManager* UIManager = GameInstance->GetUIManager();

    if (IsValid(UIManager) == false)
    {
        DEBUG_LOG("Handle_STATUS_RESPONSE Error. UIManager is Null.");
        return false;
    }

    FUserCharacter UserChracter;
    UserChracter.SetUserChracterData(pkt.usercharacter());
    UIManager->UpdatedPlayerInfo.Broadcast(UserChracter);
    return true;
}
bool Handle_GET_SKILL_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::GetSkillResponsePacket& pkt) {
    TArray<FSkillData> skillDatas;
    for (auto& skill : pkt.skill()) {
        FSkillData skillData;
        skillData.MakeSkillData(skill);

        skillDatas.Add(skillData);
    }

    GameInstance->GetSkillManager()->SetSelectedSkills(skillDatas);

    return true;
}


bool  Handle_CHANNEL_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::ChannelResponsePacket& pkt) {
    UE_LOG(LogTemp, Log, TEXT("User Channel : %d"), pkt.channelid());
    //TODO : PlayerManager or UserManager 만들면 거기에 Channel 정보도 같이 리스폰
    GameInstance->GetNetworkManager()->SendMapInfoRequest(1, pkt.channelid());
    return true;
}