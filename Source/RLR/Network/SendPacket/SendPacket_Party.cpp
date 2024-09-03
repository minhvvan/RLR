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
bool UNetworkManager::SendJoinParty(int partyId) {
    if (!MainServerSocket) return false;

    Protocol::CS_JoinPartyRequest packet;

    packet.set_userseq(UserSeq);
    packet.set_partyid(partyId);

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
bool UNetworkManager::SendLeaveParty(int partyId) {
    if (!MainServerSocket) return false;

    Protocol::CS_LeavePartyRequest packet;

    packet.set_userseq(UserSeq);
    packet.set_partyid(partyId);

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