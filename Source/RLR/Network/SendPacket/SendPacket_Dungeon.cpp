// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "Network/LoadBalancerClient.h"
#include <Networking.h>
#include "Network/FNetworkReceiver.h"
#include <Network/Buffer.h>
#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Proto/Packet.pb.h"
#include "Network/Proto/Dungeon.pb.h"



bool UNetworkManager::SendMatchMaking(int64 mapId) {
    if (!MainServerSocket) return false;

    Protocol::CS_MatchMakingRequest packet;

    packet.set_mapid(mapId);
    packet.set_userseq(GameInstance->GetUserSeq());

    SEND_PACKET(packet);
}

