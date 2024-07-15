// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/InfoPacketHandler.h"
#include <GameManager/RLRStruct.h>
#include "GameManager/GameManager.h"
#include "GameManager/MonsterManager.h"
#include "GameManager/InventoryManager.h"

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
    return true;
}