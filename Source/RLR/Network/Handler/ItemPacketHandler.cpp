// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/ItemPacketHandler.h"
#include <GameManager/RLRStruct.h>
#include "GameManager/GameManager.h"
#include "GameManager/InventoryManager.h"
#include "ClientPacketHandler.h"
//bool Handle_ITEM_ADD_REQUEST(TSharedPtr<PacketSession>& session, Protocol::ItemAddRequestPacket& pkt)
//{
//    FItemData itemData;
//
//    itemData.MakeItemData(pkt.item());
//    GameInstance->GetInventoryManager()->AddItem(itemData);
//    return true;
//}
//bool Handle_ITEM_USE_REQUEST(TSharedPtr<PacketSession>& session, Protocol::ItemUseRequestPacket& pkt)
//{
//    // Handle item use
//    return true;
//}