// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/CertificationPacketHandler.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
// Login Handlers
bool Handle_LOGIN_REQUEST(TSharedPtr<PacketSession>& session, Protocol::LoginRequestPacket& pkt)
{
    // Handle login request
    return true;
}

bool Handle_LOGIN_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::LoginResponsePacket& pkt)
{
    FString serverAddress = UTF8_TO_TCHAR(pkt.gameserveraddress().c_str());
    GameInstance->GetNetworkManager()->ConnectToLobbyServer(serverAddress, pkt.gameserverport());
    return true;
}
bool Handle_ENTER_GAME_REQUEST(TSharedPtr<PacketSession>& session, Protocol::EnterGamePacket& pkt)
{
    return false;
}
bool Handle_ENTER_GAME_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::EnterGameResponsePacket& pkt)
{
    if (pkt.success())
    {
        FString MainServerAddress = UTF8_TO_TCHAR(pkt.mainserveraddress().c_str());
        FString MonsterServerAddress = UTF8_TO_TCHAR(pkt.monsterserveraddress().c_str());
        GameInstance->GetNetworkManager()->ConnectToMainServer(MainServerAddress, pkt.mainserverport());
        GameInstance->GetNetworkManager()->ConnectToMonsterServer(MonsterServerAddress, pkt.monsterserverport());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to enter game"));
    }

    return true;
}