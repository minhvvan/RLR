// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/PlayerManager.h"

#include "Network/LoadBalancerClient.h"
#include <Networking.h>
#include "Network/FNetworkReceiver.h"
#include <Network/Buffer.h>
#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Proto/Packet.pb.h"
#include "Network/Proto/Skill.pb.h"
#include "Network/Proto/Item.pb.h"
#include "Network/Proto/Cheat.pb.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

/*

    치트 관련 패킷

    현석님이 관련 패킷이랑 기능을 서버에서 만들어주면 연결.

*/

bool UNetworkManager::SendCreateItemCheatPacket(int32 Seq)
{
	Protocol::CS_CreateItemCheatPacket packet;

    int32 CheatUserSeq = GameInstance->GetUserSeq();
    packet.set_userseq(CheatUserSeq);
	packet.set_itemseq(Seq);
	SEND_PACKET(packet);
    return false;
}

bool UNetworkManager::SendCreateSkillCheatPacket(int32 Seq)
{
    Protocol::CS_CreateSkillCheatPacket packet;
    packet.set_skillseq(Seq);
    SEND_PACKET(packet);
    DEBUG_INCOMPLETE;
    return false;
}

bool UNetworkManager::SendCreateMonsterCheatPacket(int32 Seq)
{
    Protocol::CS_CreateMonsterCheatPacket packet;
    packet.set_monsterseq(Seq);
    auto sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
    SendToMonsterSocket(sendBuffer);
    DEBUG_INCOMPLETE;
    return false;
}

