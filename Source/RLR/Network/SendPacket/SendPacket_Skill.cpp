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
#include "Structs/SkillStructs.h"

/*

    스킬 관련 패킷

*/


bool UNetworkManager::SendChangeSkillPacket(const FSkillData* SkillData, int skillIdx) {
    if (!MainServerSocket) return false;

    Protocol::CS_SkillChangeRequestPacket packet;

    packet.set_skillidx(skillIdx);
    packet.set_userseq(UserSeq);
    packet.set_skillseq(SkillData->SkillSeq);

    TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
    bool bSuccess = SendToMainSocket(sendBuffer);

    if (!bSuccess) {
        UE_LOG(LogTemp, Log, TEXT("패킷 송신 실패"));

    }
    else {
        UE_LOG(LogTemp, Log, TEXT("패킷 송신 성공"));
    }
    return bSuccess;
}

bool UNetworkManager::SendAddSkillPacket(int skillSeq) {
    if (!MainServerSocket) return false;

    Protocol::CS_SkillAddRequestPacket packet;

 
    packet.set_userseq(UserSeq);
    packet.set_skillseq(skillSeq);

    TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
    bool bSuccess = SendToMainSocket(sendBuffer);

    if (!bSuccess) {
        UE_LOG(LogTemp, Log, TEXT("패킷 송신 실패"));

    }
    else {
        UE_LOG(LogTemp, Log, TEXT("패킷 송신 성공"));
    }
    return bSuccess;
}