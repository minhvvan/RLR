// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkManager.h"
#include "../Network/LoadBalancerClient.h"
#include <Networking.h>
#include "../Network/FNetworkReceiver.h"
#include <Network/Buffer.h>
#include "../Network/ClientPacketHandler.h"
#include "../Network/Packet.pb.h"
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

    ConnectToMainServer(MainServerAddress, MainServerPort);
    ConnectToMonsterServer(MonsterServerAddress, MonsterServerPort);
}
void UNetworkManager::ConnectToLobbyServer(const FString& ServerAddress, int32 Port)
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
        SendPlayerPacket(1);

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

    if (MainServerSocket->Connect(*Addr))
    {
        MainServerReceiver = MakeShared<FNetworkReceiver>(MainServerSocket);
        MainServerThread = FRunnableThread::Create(MainServerReceiver.Get(), TEXT("MainServerReceiverThread"));
        SendStatusPacket(1);
        SendInventoryPacket(1);
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

    if (MonsterServerSocket->Connect(*Addr))
    {
        MonsterServerReceiver = MakeShared<FNetworkReceiver>(MonsterServerSocket);
        MonsterServerThread = FRunnableThread::Create(MonsterServerReceiver.Get(), TEXT("MonsterServerReceiverThread"));
        SendMapInfoRequest(1);
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
bool UNetworkManager::SendMapInfoRequest(int64 mapId) {

     if (!MonsterServerSocket) return false;

    Protocol::MapMonsterInfoRequestPacket packet;
    packet.set_mapid(mapId);
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
bool UNetworkManager::SendPlayerPacket(int32 playerSeq)
{
    if (!LobbyServerSocket) return false;

    Protocol::CharacterRequestPacket packet;
    packet.set_playerseq(playerSeq);
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
bool UNetworkManager::SendStatusPacket(int32 userSeq)
{
    if (!MainServerSocket) return false;

    Protocol::StatusRequestPacket packet;
    packet.set_userseq(userSeq);
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
bool UNetworkManager::SendInventoryPacket(int32 userSeq)
{
    if (!MainServerSocket) return false;

    Protocol::InventoryRequestPacket packet;
    packet.set_userseq(userSeq);
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