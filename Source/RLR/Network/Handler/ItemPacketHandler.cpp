// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/ItemPacketHandler.h"
#include <GameManager/RLRStruct.h>
#include "GameManager/GameManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/MonsterManager.h"
#include "GameManager/ObjectManager.h"
#include "ClientPacketHandler.h"
bool Handle_ITEM_ADD_REQUEST(TSharedPtr<PacketSession>& session, Protocol::ItemAddRequestPacket& pkt)
{
    FItemData itemData;

    itemData.MakeItemData(pkt.item());
    GameInstance->GetInventoryManager()->AddItem(itemData);
    return true;
}
bool Handle_ITEM_USE_REQUEST(TSharedPtr<PacketSession>& session, Protocol::ItemUseRequestPacket& pkt)
{
    // Handle item use
    return true;
}

bool Handle_DROP_REQUEST(TSharedPtr<PacketSession>& session, Protocol::DropRequest& pkt)
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
bool Handle_EQUIP_INFO_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::EquipInfoResponse& pkt) {
    //Equip 으로 변경 

	TArray<FItemData> ItemDataList;
	for (int32 i = 0; i < pkt.equips_size(); i++) {
		FItemData itemData;
		itemData.MakeItemData(pkt.equips().at(i));
        ItemDataList.Add(itemData);
	}

    /*
        인벤토리 업데이트 && 장비창 업데이트

        플레이어 본래 스탯은 어디서 끌고와야 하지?
    */

    for (const FItemData& ItemData : ItemDataList)
    {
       bool Ret = GameInstance->GetInventoryManager()->EquipItem(ItemData.ITEM_SEQ);
       if (Ret == false)
       {
            //false 가 나왔다는 건 인벤토리에 없는데 아이템 장착을 시도했다는 소리.
            //즉, false가 나오면 안된다.
           DEBUG_MESSAGE;
       }
    }


	GameInstance->GetInventoryManager()->Update();
    return true;
}

//장비 장착 , 교체 해제는 X
bool Handle_EQUIP_CHANGE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::EquipChangeRespnse& pkt) {
    // pkt.success 만 확인

    return true;
}