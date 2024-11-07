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
#include "Network/Proto/NPC.pb.h"

/*

    퀘스트 관련 패킷

*/

bool UNetworkManager::SendQuestAddPacket(int npcSeq, int questSeq) {
    if (!MainServerSocket) return false;

    Protocol::CS_QuestAddRequest packet;

    packet.set_userseq(GameInstance->GetUserSeq());
    packet.set_npcseq(npcSeq);
    packet.set_questseq(questSeq);


    SEND_PACKET(packet);
}
bool UNetworkManager::SendQuestCheckPacket(int questSeq) {
    if (!MainServerSocket) return false;

    Protocol::CS_QuestCheckRequest packet;

    packet.set_userseq(GameInstance->GetUserSeq());
    packet.set_questseq(questSeq);


    SEND_PACKET(packet);
}

bool UNetworkManager::SendQuestCompletePacket(int questSeq) {
    if (!MainServerSocket) return false;

    Protocol::CS_QuestCompleteRequest packet;

    packet.set_userseq(GameInstance->GetUserSeq());
    packet.set_questseq(questSeq);
    


    SEND_PACKET(packet);
}