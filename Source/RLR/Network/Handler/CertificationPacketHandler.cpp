// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/CertificationPacketHandler.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ClientPacketHandler.h"
// Login Handlers

bool Handle_LOGIN_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_LoginResponsePacket& pkt)
{
    FString serverAddress = UTF8_TO_TCHAR(pkt.gameserveraddress().c_str());
    GameInstance->GetNetworkManager()->ConnectToLobbyServer(serverAddress, pkt.gameserverport(),pkt.playerseq());
    return true;
}

bool Handle_ENTER_GAME_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_EnterGameResponsePacket& pkt)
{
    if (pkt.success())
    {
        int userSeq = 1;
       // int32 userSeq = GameInstance->GetPlayerManager()->GetPlayerCharacter()->GetActionSystemComponent()->GetStatSet<FUserCharacter>()->UserSeq;
        FString MainServerAddress = UTF8_TO_TCHAR(pkt.mainserveraddress().c_str());
        FString MonsterServerAddress = UTF8_TO_TCHAR(pkt.monsterserveraddress().c_str());
        
        GameInstance->GetNetworkManager()->ConnectToMonsterServer(MonsterServerAddress, pkt.monsterserverport());
        GameInstance->GetNetworkManager()->ConnectToMainServer(MainServerAddress, pkt.mainserverport());
        GameInstance->GetNetworkManager()->SendServerRequest(userSeq);
        GameInstance->GetNetworkManager()->SendGetSkillPacket(userSeq);
        GameInstance->GetNetworkManager()->SendNPCInfoPacket(userSeq);
        GameInstance->GetNetworkManager()->SendUserQuestPacket(userSeq);
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
     //GameInstance->GetLobbyManager()->SetUsersData();



    return true;
}