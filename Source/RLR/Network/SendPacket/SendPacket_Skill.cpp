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
#include "Network/Proto/Skill.pb.h"
#include "Structs/SkillStructs.h"

/*

    스킬 관련 패킷

*/


bool UNetworkManager::SendChangeSkillPacket(const FSkillData* SkillData, int skillIdx) {
    if (!MainServerSocket) return false;

    Protocol::CS_SkillChangeRequestPacket packet;

    int32 SkillUserSeq = GameInstance->GetUserSeq();
    packet.set_skillidx(skillIdx);
    packet.set_userseq(SkillUserSeq);
    packet.set_skillseq(SkillData->SkillSeq);

    SEND_PACKET(packet);
}

bool UNetworkManager::SendAddSkillPacket(int skillSeq) {
    if (!MainServerSocket) return false;

    Protocol::CS_SkillAddRequestPacket packet;

    int32 SkillUserSeq = GameInstance->GetUserSeq();
    packet.set_userseq(SkillUserSeq);
    packet.set_skillseq(skillSeq);

    SEND_PACKET(packet);
}