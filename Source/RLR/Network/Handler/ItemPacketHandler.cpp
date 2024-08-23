// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/ItemPacketHandler.h"
#include <GameManager/RLRStruct.h>
#include "GameManager/GameManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/MonsterManager.h"
#include "GameManager/ObjectManager.h"
#include "ClientPacketHandler.h"
bool Handle_ADD_ITEM_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_AddItemResponse& pkt)
{
    
    return true;
}
bool Handle_ITEM_USE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_ItemUseResponsePacket& pkt)
{
    // Handle item use
    return true;
}

bool Handle_DROP_REQUEST(TSharedPtr<PacketSession>& session, Protocol::SC_DropRequest& pkt)
{
    int64 objectId = pkt.objectid();
    int value = pkt.value();
    int64 monsterId = pkt.monsterid();
  /*  TArray<FInteractData> DropDatas;
    FInteractData DropData;
    DropData.MakeObjectData();
    DropDatas.Add(DropData);
    GameInstance->GetObjectManager()->SetObjectData(DropDatas);*/

    return true;
}

// 장비창 정보 
bool Handle_EQUIP_INFO_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_EquipInfoResponse& pkt) {
    //Equip 으로 변경 

    /*TArray<FItemData> itemDatas;
    for (int32 i = 0; i < pkt.equips_size(); i++) {
        FItemData itemData;
        itemData.MakeItemData(pkt.equips().at(i));

        itemDatas.Add(itemData);
    }

    GameInstance->GetInventoryManager()->GetItemList(itemDatas);*/
    return true;
}

//장비 장착 , 교체 해제는 X
bool Handle_EQUIP_CHANGE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_EquipChangeRespnse& pkt) {
    // pkt.success 만 확인

    return true;
}