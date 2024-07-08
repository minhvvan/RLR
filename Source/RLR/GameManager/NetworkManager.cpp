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
    }
}
void UNetworkManager::Update()
{
    // Periodic updates if needed
}

bool UNetworkManager::SendToMainSocket(TSharedPtr<SendBuffer> sendBuffer)
{
    int32 BytesSent = 0;
    MainServerSocket->Send(sendBuffer->GetBuffer(), sendBuffer->Capacity(), BytesSent);
    return true;
}

bool UNetworkManager::SendToMonsterSocket(TSharedPtr<SendBuffer> sendBuffer)
{
    int32 BytesSent = 0;
    MonsterServerSocket->Send(sendBuffer->GetBuffer(), sendBuffer->Capacity(), BytesSent);
    return true;
}