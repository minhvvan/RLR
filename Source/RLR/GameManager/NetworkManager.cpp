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
#include "RLR.h"
#include "GameManager/GameManager.h"
#include "GameManager/LiteralManager.h"

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

bool UNetworkManager::ConnectToLoginServer(const FString& serverAddress, int32 port) {
    
    LoginServerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, RLRLITERAL.Network_LoginServerSocket, false);
    FIPv4Address IP;
    FIPv4Address::Parse(serverAddress, IP);

    TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    Addr->SetIp(IP.Value);
    Addr->SetPort(port);


    if (LoginServerSocket->Connect(*Addr))
    {
        LoginServerReceiver = MakeShared<FNetworkReceiver>(LoginServerSocket);
        LoginServerThread = FRunnableThread::Create(LoginServerReceiver.Get(), *RLRLITERAL.Network_LoginServerReceiverThread);
    }
    return true;
}
void UNetworkManager::ConnectToLobbyServer(const FString& ServerAddress, int32 Port, int32 playerSeq)
{
    LobbyServerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, RLRLITERAL.Network_LobbyServerSocket, false);
    FIPv4Address IP;
    FIPv4Address::Parse(ServerAddress, IP);

    TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    Addr->SetIp(IP.Value);
    Addr->SetPort(Port);

    if (LobbyServerSocket->Connect(*Addr))
    {
        LobbyServerReceiver = MakeShared<FNetworkReceiver>(LobbyServerSocket);
        LobbyServerThread = FRunnableThread::Create(LobbyServerReceiver.Get(), *RLRLITERAL.LevelPath_Lobby);
        GameInstance->SetPlayerSeq(playerSeq);
        
    }
}
void UNetworkManager::ConnectToMainServer(const FString& ServerAddress, int32 Port)
{
    MainServerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, RLRLITERAL.Network_MainServerSocket, false);
    FIPv4Address IP;
    FIPv4Address::Parse(ServerAddress, IP);

    TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    Addr->SetIp(IP.Value);
    Addr->SetPort(Port);
    MainServerSocket->SetNonBlocking(true);
    if (MainServerSocket->Connect(*Addr))
    {
        MainServerReceiver = MakeShared<FNetworkReceiver>(MainServerSocket);
        MainServerThread = FRunnableThread::Create(MainServerReceiver.Get(), *RLRLITERAL.Network_MainServerReceiverThread);
        
    }
}

void UNetworkManager::ConnectToMonsterServer(const FString& ServerAddress, int32 Port)
{
    MonsterServerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, RLRLITERAL.Network_MonsterServerSocket, false);
    FIPv4Address IP;
    FIPv4Address::Parse(ServerAddress, IP);

    TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    Addr->SetIp(IP.Value);
    Addr->SetPort(Port);
    MonsterServerSocket->SetNonBlocking(true);
    if (MonsterServerSocket->Connect(*Addr))
    {
        MonsterServerReceiver = MakeShared<FNetworkReceiver>(MonsterServerSocket);
        MonsterServerThread = FRunnableThread::Create(MonsterServerReceiver.Get(), *RLRLITERAL.Network_MonsterServerReceiverThread);

    }
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
    packet.set_mapid(GameInstance->GetMapId());
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
    packet.set_playerseq(GameInstance->GetPlayerSeq());
    TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
    bool bSuccess = SendToLobbySocket(sendBuffer);

    if (!bSuccess) {
        UE_LOG(LogTemp, Log, TEXT("패킷 송신 실패"));

    }
    else {
        UE_LOG(LogTemp, Log, TEXT("Character Request 패킷 송신 성공"));
    }
    return bSuccess;

}

bool UNetworkManager::SendStatusPacket()
{
    if (!MainServerSocket) return false;

    Protocol::CS_StatusRequestPacket packet;
    packet.set_userseq(GameInstance->GetUserSeq());
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
    packet.set_userseq(GameInstance->GetUserSeq());
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
    packet.mutable_skill()->set_userseq(GameInstance->GetUserSeq());
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
    packet.set_userseq(GameInstance->GetUserSeq());

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

    packet.set_userseq(GameInstance->GetUserSeq());

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
bool UNetworkManager::SendMovePacket(FVector vector) {

    if (!MainServerSocket && !MonsterServerSocket) return false;

    int userSeq = GameInstance->GetUserSeq();
    int mapid = GameInstance->GetMapId();
    int channelId = GameInstance->GetChannelId();
    if (userSeq == 0)
    {
        RLR_LOG(LogRLR, Log, TEXT("UserSeq is Invalid: %d"), userSeq);
        return false;
    }

    if (mapid == 0)
    {
        RLR_LOG(LogRLR, Log, TEXT("MapID is Invalid: %d"), mapid);
        return false;
    }

    if (channelId == 0)
    {
        RLR_LOG(LogRLR, Log, TEXT("ChannelID is Invalid: %d"), channelId);
        return false;
    }

    Protocol::CS_MoveRequestPacket packet;
    packet.set_userseq(userSeq);
    packet.set_mapid(mapid);
    packet.set_channelid(channelId);
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
        RLR_LOG(LogRLR, Log, TEXT("패킷 송신 성공"));
    }


    return aSuccess && bSuccess;
}
bool UNetworkManager::SendNPCInfoPacket() {

    if (!MainServerSocket) return false;
    Protocol::CS_NPCInfoRequest packet;
    packet.set_mapid(GameInstance->GetMapId());
    UE_LOG(LogTemp, Log, TEXT("Map Id : %d"), GameInstance->GetMapId());
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
    packet.set_userseq(GameInstance->GetUserSeq());
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
    packet.set_userseq(userSeq);

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