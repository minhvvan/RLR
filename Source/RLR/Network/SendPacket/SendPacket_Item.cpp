// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/GameManager.h"

#include "Network/LoadBalancerClient.h"
#include <Networking.h>
#include "Network/FNetworkReceiver.h"
#include <Network/Buffer.h>
#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Proto/Packet.pb.h"
#include "Network/Proto/Item.pb.h"
#include "Structs/ItemStructs.h"

/*

    Item.proto 패킷

*/


bool UNetworkManager::SendEquipChangePacket(const FItemData& ItemData)
{
    if (!MainServerSocket) return false;

    /*
        아이템 장착.
    */

    Protocol::CS_EquipChangeRequest packet;

    int32 OjbectId = ItemData.ITEM_SEQ;
    //int32 UserSeq = GameInstance->GetPlayerManager()->GetUserSeq();

    packet.set_objectid(OjbectId);
    packet.set_userseq(UserSeq);
    Protocol::Equip* EquipItem = packet.mutable_item();

    FItemData temp = ItemData;
    Protocol::Equip CopyData = temp.MakeEquipPacket();
    EquipItem->CopyFrom(CopyData);


    SEND_PACKET(packet);

    return false;
}

bool UNetworkManager::SendUnEquipChangePacket(const FItemData& ItemData)
{
    if (!MainServerSocket) return false;

    /*
        아이템 해제.
        아직 proto에 만들어진 패킷이 없어서 임시 구현
    */

    Protocol::CS_EquipChangeRequest packet;

    int32 OjbectId = ItemData.ITEM_SEQ;

    packet.set_objectid(OjbectId);
    packet.set_userseq(UserSeq);
    Protocol::Equip* EquipItem = packet.mutable_item();

    FItemData temp = ItemData;
    Protocol::Equip CopyData = temp.MakeEquipPacket();
    EquipItem->CopyFrom(CopyData);


    SEND_PACKET(packet);

    return false;
}