// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "Network/LoadBalancerClient.h"
#include <Networking.h>
#include "Network/FNetworkReceiver.h"
#include <Network/Buffer.h>
#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Proto/Packet.pb.h"

bool UNetworkManager::SendCreateParty() {
    if (!MainServerSocket) return false;

    Protocol::CS_CreatePartyRequest packet;

    packet.set_userseq(UserSeq);
    SEND_PACKET(packet);
}
bool UNetworkManager::SendJoinParty(int partyId) {
    if (!MainServerSocket) return false;

    Protocol::CS_JoinPartyRequest packet;

    packet.set_userseq(UserSeq);
    packet.set_partyid(partyId);

    SEND_PACKET(packet);
}
bool UNetworkManager::SendLeaveParty(int partyId) {
    if (!MainServerSocket) return false;

    Protocol::CS_LeavePartyRequest packet;

    packet.set_userseq(UserSeq);
    packet.set_partyid(partyId);

    SEND_PACKET(packet);
}