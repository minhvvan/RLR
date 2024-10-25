// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/GameManager.h"
#include "Structs/ItemStructs.h"
#include "GameManager/LevelManager.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

#include "Network/LoadBalancerClient.h"
#include <Networking.h>
#include "Network/FNetworkReceiver.h"
#include <Network/Buffer.h>
#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Proto/Packet.pb.h"
#include "Network/Proto/Map.pb.h"

/*
	Map 관련 패킷.
*/
bool UNetworkManager::SendContentMap(int64 mapId) {
    if (!MainServerSocket) return false;

    Protocol::CS_MapContentRequest packet;
    packet.set_mapid(mapId);
    packet.set_userseq(UserSeq);

    SEND_PACKET(packet);
}
bool UNetworkManager::SendMoveMap() {
    Protocol::CS_MapMoveRequest packet;

    packet.set_userseq(UserSeq);

    SEND_PACKET(packet);
}