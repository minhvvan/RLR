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
#include "Network/Proto/Item.pb.h"
#include "Network/Proto/Trade.pb.h"
#include "Network/Proto/Skill.pb.h"

/*
    Good 관련 패킷.
*/

bool UNetworkManager::SendUserGoodPacket()
{
    if (!MainServerSocket) return false;

    /*
        거래 요청 보내기
    */

    int32 MySeq = GameInstance->GetUserSeq();

    Protocol::CS_UserGoodRequest packet;
    packet.set_userseq(MySeq);
    SEND_PACKET(packet);
    return false;
}

bool UNetworkManager::SendPlayerGoodPacket()
{
    if (!MainServerSocket) return false;

    /*
        거래 요청 수락하기
    */

    int32 MySeq = GameInstance->GetUserSeq();

    Protocol::CS_PlayerGoodRequest packet;
    packet.set_userseq(MySeq);
    SEND_PACKET(packet);
    return false;
}
