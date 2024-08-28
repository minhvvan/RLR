// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/CertificationPacketHandler.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ClientPacketHandler.h"
// Login Handlers

static bool LoginState = false;
bool Handle_LOGIN_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_LoginResponsePacket& pkt)
{
    FString serverAddress = UTF8_TO_TCHAR(pkt.gameserveraddress().c_str());
    GameInstance->GetNetworkManager()->ConnectToLobbyServer(serverAddress, pkt.gameserverport(),pkt.playerseq());
    return true;
}

bool Handle_ENTER_GAME_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_EnterGameResponsePacket& pkt)
{
    UE_LOG(LogTemp, Log, TEXT("Enter Game RESPONSE 전송 받음"));
    if (pkt.success())
    {
        

        FString MainServerAddress = UTF8_TO_TCHAR(pkt.mainserveraddress().c_str());
        FString MonsterServerAddress = UTF8_TO_TCHAR(pkt.monsterserveraddress().c_str());
        
        GameInstance->GetNetworkManager()->ConnectToMonsterServer(MonsterServerAddress, pkt.monsterserverport());
        GameInstance->GetNetworkManager()->ConnectToMainServer(MainServerAddress, pkt.mainserverport());
        GameInstance->GetNetworkManager()->SendServerRequest();
        GameInstance->GetNetworkManager()->SendGetSkillPacket();
        GameInstance->GetNetworkManager()->SendUserQuestPacket();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to enter game"));
    }

    return true;
}

bool Handle_CHARACTER_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_UserResponsePacket& pkt) {

    

    TArray<FUserCharacter> users;
    for (auto& user : pkt.users()) {
        FUserCharacter Fuser;
        Fuser.MakeUserCharacter(user);
        users.Add(Fuser);
    }
    UE_LOG(LogTemp, Error, TEXT("User Seq : %d"), pkt.users().at(0).userseq());
    GameInstance->GetNetworkManager()->SetUserSeq(pkt.users().at(0).userseq());
    GameInstance->GetNetworkManager()->SetMapId(pkt.users().at(0).mapid());
    GameInstance->GetNetworkManager()->SendEnterPacket(pkt.users().at(0).userseq());
     //GameInstance->GetLobbyManager()->SetUsersData();



    return true;
}