// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/CertificationPacketHandler.h"

#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/LevelManager.h"

#include "UI/Title/TitleMainUI.h"
#include "UI/Lobby/LobbyMainUI.h"

#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ClientPacketHandler.h"
#include "Structs/PlayerStructs.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "RLR.h"
bool Handle_SERVERLIST_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_LoginResponsePacket& pkt)
{
    /*
        타이틀에서 플레이어가 접속 가능한 서버 리스트 업데이트.
        패킷 제대로 안해놨으니 수정 바람.
    */

    UUIManager* UIManager = GameInstance->GetUIManager();
    if (IsValid(UIManager) == false)
        return false;


    UTitleMainUI* TitleMainUI = UIManager->GetPage<UTitleMainUI>(FGameplayTagManager::Get().Page_InGame);
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

// Login Handlers

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
  

   return true;
}

bool Handle_ENTER_GAME_FROM_LOBBY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_EnterGameResponsePacket& pkt)
{
    /*
    *   임시로 구현.
        타이틀 -> 로비 -> 인게임 이동이 완벽해지면 Handle_ENTER_GAME_RESPONSE 대신 해주기.
    */
    /*
        로딩 화면이 필요할거 같다.
        레벨 이동에는 딜레이가 존재하고, 딜레이 동안 로딩화면을 보여주면서, 
        레벨 이동이 완료되었을 때 ConnectToServer 같은 것들이 진행되어야 한다.
    */

    /*
    *   checkf(IsInGameThread(), TEXT("Enumerating in-memory assets can only be done on the game thread; it uses non-threadsafe UE::AssetRegistry::Filtering globals."));
        레벨 이동 특성상 쓰레드 문제가 발생한다.
        워커쓰레드 -> 메인 쓰레드에서 실행하게 해줘야 할 거 같은데.. 
 
    */
    FString MainServerAddress = UTF8_TO_TCHAR(pkt.mainserveraddress().c_str());
    FString MonsterServerAddress = UTF8_TO_TCHAR(pkt.monsterserveraddress().c_str());
    int32 MainPort = pkt.mainserverport();
    int32 MonsterPort = pkt.monsterserverport();

    GameInstance->GetLevelManager()->EnterLevel("Main", MainServerAddress, MainPort, MonsterServerAddress, MonsterPort);
    return true;
}

bool Handle_ENTER_GAME_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_EnterGameResponsePacket& pkt)
{
    UE_LOG(LogTemp, Log, TEXT("Enter Game RESPONSE 전송 받음"));
    if (pkt.success())
    {
        //레벨 이름은 Main을 사용하지 말것. 왠지 모르지만 로딩이 안됨.
        FString MainServerAddress = UTF8_TO_TCHAR(pkt.mainserveraddress().c_str());
        FString MonsterServerAddress = UTF8_TO_TCHAR(pkt.monsterserveraddress().c_str());
        int32 MainServerPort = pkt.mainserverport();
        int32 MonsterServerPort = pkt.monsterserverport();     
        GameInstance->GetLevelManager()->EnterLevel("TestMap2", MainServerAddress, MainServerPort, MonsterServerAddress, MonsterServerPort);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to enter game"));
    }

    return true;
}

bool Handle_CHARACTER_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_UserResponsePacket& pkt) {

    ULobbyMainUI* LobbyMainUI = GameInstance->GetUIManager()->GetPage<ULobbyMainUI>(FGameplayTagManager::Get().Page_InGame);

    if (IsValid(LobbyMainUI) == false)
        return false;

    TArray<FUserCharacter> users;
    for (auto& user : pkt.users()) {
        FUserCharacter UserChracter;
        UserChracter.MakeUserCharacter(user);
        users.Add(UserChracter);
      
    }
    LobbyMainUI->AddUserCharacter(users);
    return true;
}
