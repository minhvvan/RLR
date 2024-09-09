// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkManager.h"
#include "Network/LoadBalancerClient.h"
#include <Networking.h>
#include "Network/FNetworkReceiver.h"
#include <Network/Buffer.h>
#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Proto/Packet.pb.h"
#include "Network/Proto/Skill.pb.h"
#include "Structs/UtilStructs.h"
#include "Network/Proto/Item.pb.h"

void UNetworkManager::SetLoadBalancer(std::string host, int32 port)
{
    LoadBalancer = new LoadBalancerClient(host, port);
}

void UNetworkManager::RequestServerAddresses(int32 userSeq)
{
    UE_LOG(LogTemp, Log, TEXT("메인 주소 가져오기 시작"));
    std::string response = LoadBalancer->RequestServer(userSeq);
    TArray<FString> serverAddresses;
    FString(response.c_str()).ParseIntoArray(serverAddresses, TEXT(";"), true);

    if (serverAddresses.Num() != 4)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get valid server addresses from LoadBalancer"));
        return;
    }

    FString MainServerAddress = serverAddresses[0];
    int32 MainServerPort = FCString::Atoi(*serverAddresses[1]);
    FString MonsterServerAddress = serverAddresses[2];
    int32 MonsterServerPort = FCString::Atoi(*serverAddresses[3]);

    UE_LOG(LogTemp, Log, TEXT("Got server addresses from LoadBalancer: MainServer=%s:%d, MonsterServer=%s:%d"), *MainServerAddress, MainServerPort, *MonsterServerAddress, MonsterServerPort);
    ConnectToMonsterServer(MonsterServerAddress, MonsterServerPort);
    ConnectToMainServer(MainServerAddress, MainServerPort);
    
}
void UNetworkManager::ConnectToLobbyServer(const FString& ServerAddress, int32 Port, int32 playerSeq)
{
    LobbyServerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("LobbyServerSocket"), false);
    FIPv4Address IP;
    FIPv4Address::Parse(ServerAddress, IP);

    TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    Addr->SetIp(IP.Value);
    Addr->SetPort(Port);

    if (LobbyServerSocket->Connect(*Addr))
    {
        LobbyServerReceiver = MakeShared<FNetworkReceiver>(LobbyServerSocket);
        LobbyServerThread = FRunnableThread::Create(LobbyServerReceiver.Get(), TEXT("LobbyServerReceiverThread"));
        SetPlayerSeq(playerSeq);
        SendPlayerPacket();
    }
}
void UNetworkManager::ConnectToMainServer(const FString& ServerAddress, int32 Port)
{
    MainServerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("MainServerSocket"), false);
    FIPv4Address IP;
    FIPv4Address::Parse(ServerAddress, IP);

    TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    Addr->SetIp(IP.Value);
    Addr->SetPort(Port);
    MainServerSocket->SetNonBlocking(true);
    if (MainServerSocket->Connect(*Addr))
    {
        MainServerReceiver = MakeShared<FNetworkReceiver>(MainServerSocket);
        MainServerThread = FRunnableThread::Create(MainServerReceiver.Get(), TEXT("MainServerReceiverThread"));
        
    }
}

void UNetworkManager::ConnectToMonsterServer(const FString& ServerAddress, int32 Port)
{
    MonsterServerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("MonsterServerSocket"), false);
    FIPv4Address IP;
    FIPv4Address::Parse(ServerAddress, IP);

    TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    Addr->SetIp(IP.Value);
    Addr->SetPort(Port);
    MonsterServerSocket->SetNonBlocking(true);
    if (MonsterServerSocket->Connect(*Addr))
    {
        MonsterServerReceiver = MakeShared<FNetworkReceiver>(MonsterServerSocket);
        MonsterServerThread = FRunnableThread::Create(MonsterServerReceiver.Get(), TEXT("MonsterServerReceiverThread"));

    }
}
void UNetworkManager::SetUserSeq(int32 userSeq)
{
    this->UserSeq = userSeq;

}
void UNetworkManager::SetPlayerSeq(int32 playerSeq)
{
    this->PlayerSeq = playerSeq;
}
void UNetworkManager::SetMapId(int64 mapId) {

    this->MapId = mapId;
}
void UNetworkManager::Update()
{
    // Periodic updates if needed
}

bool UNetworkManager::SendToMainSocket(TSharedPtr<SendBuffer> sendBuffer)
{
    int32 BytesSent = 0;
    return   MainServerSocket->Send(sendBuffer->GetBuffer(), sendBuffer->Capacity(), BytesSent);
}

bool UNetworkManager::SendToMonsterSocket(TSharedPtr<SendBuffer> sendBuffer)
{
    int32 BytesSent = 0;
    return  MonsterServerSocket->Send(sendBuffer->GetBuffer(), sendBuffer->Capacity(), BytesSent);
}
bool UNetworkManager::SendToLobbySocket(TSharedPtr<SendBuffer> sendBuffer)
{
    int32 BytesSent = 0;
    return  LobbyServerSocket->Send(sendBuffer->GetBuffer(), sendBuffer->Capacity(), BytesSent);
}
bool UNetworkManager::SendMapInfoRequest(int64 channelId) {

    if (!MonsterServerSocket) return false;

    Protocol::CS_MapMonsterInfoRequestPacket packet;
    packet.set_mapid(MapId);
    packet.set_channelid(channelId);
    TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
    bool bSuccess = SendToMonsterSocket(sendBuffer);

    if (!bSuccess) {
        UE_LOG(LogTemp, Log, TEXT("패킷 송신 실패"));
        return false;
    }
    else {
        UE_LOG(LogTemp, Log, TEXT("패킷 송신 성공"));
        return true;
    }
}
bool UNetworkManager::SendPlayerPacket()
{
    if (!LobbyServerSocket) return false;

    Protocol::CS_CharacterRequestPacket packet;
    packet.set_playerseq(PlayerSeq);
    TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
    bool bSuccess = SendToLobbySocket(sendBuffer);

    if (!bSuccess) {
        UE_LOG(LogTemp, Log, TEXT("패킷 송신 실패"));

    }
    else {
        UE_LOG(LogTemp, Log, TEXT("패킷 송신 성공"));
    }
    return bSuccess;

}
bool UNetworkManager::SendStatusPacket()
{
    if (!MainServerSocket) return false;

    Protocol::CS_StatusRequestPacket packet;
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
bool UNetworkManager::SendInventoryPacket()
{
    if (!MainServerSocket) return false;

    Protocol::CS_InventoryRequestPacket packet;
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

bool UNetworkManager::SendAttackPacket(FAttackResult attackResult)
{
    if (!MainServerSocket) return false;

    Protocol::CS_AttackRequestPacket packet;
    packet.mutable_skill()->set_skillseq(attackResult.SkillSeq);
    packet.mutable_skill()->set_level(attackResult.Level);
    packet.mutable_skill()->set_userseq(attackResult.UserSeq);
    packet.mutable_skill()->set_timestamp(attackResult.Timestamp);
    for (int i = 0; i < attackResult.TargetSeq.Num(); i++) {
        packet.mutable_skill()->add_targetseq(attackResult.TargetSeq[i]);
    }
    TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
    bool bSuccess = SendToMainSocket(sendBuffer);

    if (!bSuccess) {
        UE_LOG(LogTemp, Log, TEXT("패킷 송신 실패"));

    }
    else {
        UE_LOG(LogTemp, Log, TEXT("Attack 패킷 송신 성공"));
    }
    return bSuccess;
}

bool UNetworkManager::SendGetSkillPacket() {
    if (!MainServerSocket) return false;

    Protocol::CS_GetSkillRequestPacket packet;
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

bool UNetworkManager::SendServerRequest() {
    if (!MainServerSocket) return false;

    Protocol::CS_ServerReqeustPacket packet;

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
bool UNetworkManager::SendMovePacket(FVector vector, int64 mapid, int64 channelid) {

    if (!MainServerSocket && !MonsterServerSocket) return false;
    if (UserSeq == 0) return false;

    if (UserSeq == 0) {
        return false;
    }
    Protocol::CS_MoveRequestPacket packet;
    packet.set_userseq(UserSeq);
    packet.set_mapid(mapid);
    packet.set_channelid(1);  
    packet.set_transx((float)vector.X);
    packet.set_transy((float)vector.Y);
    packet.set_transz((float)vector.Z);
    TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
    int32 BytesSent = 0;
    bool aSuccess = MainServerSocket->Send(sendBuffer->GetBuffer(), sendBuffer->Capacity(), BytesSent);
    bool bSuccess = MonsterServerSocket->Send(sendBuffer->GetBuffer(), sendBuffer->Capacity(), BytesSent);

    if (!bSuccess && !aSuccess) {
        UE_LOG(LogTemp, Error, TEXT("패킷 송신 실패"));
    }
    else {
        UE_LOG(LogTemp, Log, TEXT("패킷 송신 성공"));
    }


    return aSuccess && bSuccess;
}
bool UNetworkManager::SendNPCInfoPacket() {

    if (!MainServerSocket) return false;
    Protocol::CS_NPCInfoRequest packet;
    packet.set_mapid(MapId);
    UE_LOG(LogTemp, Log, TEXT("Map Id : %d"),MapId);
    TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
    int32 BytesSent = 0;
    bool bSuccess = SendToMainSocket(sendBuffer);

    if (!bSuccess) {
        UE_LOG(LogTemp, Error, TEXT("패킷 송신 실패"));
    }
    else {
        UE_LOG(LogTemp, Log, TEXT("NPC 패킷 송신 성공"));
    }


    return bSuccess;
}

bool UNetworkManager::SendUserQuestPacket() {

    if (!MainServerSocket) return false;
    Protocol::CS_UserQuestInfoRequest packet;
    packet.set_userseq(UserSeq);
    TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
    int32 BytesSent = 0;
    bool bSuccess = SendToMainSocket(sendBuffer);

    if (!bSuccess) {
        UE_LOG(LogTemp, Error, TEXT("User Quest 패킷 송신 실패"));
    }
    else {
        UE_LOG(LogTemp, Log, TEXT("User Quest 패킷 송신 성공"));
    }


    return bSuccess;
}

bool UNetworkManager::SendEnterPacket(int32 userSeq) {
    // 로비 ui로 이동 필요
    Protocol::CS_EnterGamePacket packet;
    packet.set_userseq(UserSeq);

    TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
    bool bSuccess =  SendToLobbySocket(sendBuffer);
    if (!bSuccess) {
        UE_LOG(LogTemp, Error, TEXT("Enter 패킷 송신 실패"));
    }
    else {
        UE_LOG(LogTemp, Log, TEXT("Enter 패킷 송신 성공"));
    }


    return bSuccess;
}