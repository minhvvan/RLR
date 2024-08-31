// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/CertificationPacketHandler.h"

#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/LevelManager.h"

#include "UI/Title/TitleMainUI.h"

#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ClientPacketHandler.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

bool Handle_SERVERLIST_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_LoginResponsePacket& pkt)
{
    /*
        타이틀에서 플레이어가 접속 가능한 서버 리스트 업데이트.
        패킷 제대로 안해놨으니 수정 바람.
    */

    UUIManager* UIManager = GameInstance->GetUIManager();
    if (IsValid(UIManager) == false)
        return false;


    UTitleMainUI* TitleMainUI = Cast<UTitleMainUI>(UIManager->GetMainUI());
    if(IsValid(TitleMainUI) == false)
        return false;
    
    //마저 완성해주기.
    //for (int32 i = 0; i < ServerListCount; i++)
    //{
    //    FServerData NewServerData;
    //    TitleMainUI->AddServerListElement(NewServerData);
    //}

    return true;
}

bool Handle_LOGIN_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_LoginResponsePacket& pkt)
{
    FString serverAddress = UTF8_TO_TCHAR(pkt.gameserveraddress().c_str());
    GameInstance->GetNetworkManager()->ConnectToLobbyServer(serverAddress, pkt.gameserverport(),pkt.playerseq());
    bool Ret = GameInstance->GetLevelManager()->LoadLevel("Lobby");
    if (Ret == false)
    {
        //TODO
        //UIManager->OpenPopup으로 경고 추가하기.
        DEBUG_LOG("Load lobby level fail");
    }

   return Ret;
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