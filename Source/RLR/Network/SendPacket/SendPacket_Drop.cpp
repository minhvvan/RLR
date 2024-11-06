// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "Network/LoadBalancerClient.h"
#include <Networking.h>
#include "Network/FNetworkReceiver.h"
#include <Network/Buffer.h>
#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Proto/Packet.pb.h"
#include "Network/Proto/Skill.pb.h"
#include "Network/Proto/Item.pb.h"
#include "Network/Proto/Skill.pb.h"

/*
	
	Drop.proto

*/

bool UNetworkManager::SendAddItemPacket(int64 itemId, int32 value)
{
    if (!MainServerSocket) return false;

    /*
        아이템 획득.
    */

    Protocol::CS_AddItemRequest packet;
   
    packet.set_objectid(itemId);
    packet.set_userseq(GameInstance->GetUserSeq());
    packet.set_value(value);

    SEND_PACKET(packet);

    return false;
}

