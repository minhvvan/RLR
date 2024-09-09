#pragma once

#include "CoreMinimal.h"
#include <Network/Buffer.h>
#include "Subsystems/GameInstanceSubsystem.h"

#include "RLRStruct.h"

#include <mutex>
#include <queue>

#include "NetworkManager.generated.h"

using namespace std;

class FNetworkReceiver;
class LoadBalancerClient;

UCLASS()
class RLR_API UNetworkManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    void SetLoadBalancer(std::string host, int32 port);

    UFUNCTION(BlueprintCallable)
    void RequestServerAddresses(int32 userSeq);
    UFUNCTION(BlueprintCallable)
    void ConnectToLobbyServer(const FString& ServerAddress, int32 Port,int32 playerSeq);
    UFUNCTION(BlueprintCallable)
    void ConnectToMainServer(const FString& ServerAddress, int32 Port);
    UFUNCTION(BlueprintCallable)
    void ConnectToMonsterServer(const FString& ServerAddress, int32 Port);
    UFUNCTION(BlueprintCallable)
    void Update();


    bool SendToMainSocket(TSharedPtr<SendBuffer> sendBuffer);
    bool SendToMonsterSocket(TSharedPtr<SendBuffer> sendBuffer);
    bool SendToLobbySocket(TSharedPtr<SendBuffer> sendBuffer);

    /*
        Title
    */

    bool SendServerListRequest();                               //접속 가능한 서버 목록을 요청한다.
    bool SendLoginRequest(int32 ServerSeq, FText ID, FText PW); //선택한 서버, 아디, 비번을 담아 로그인 시도 패킷을 보낸다.

    /*
        Lobby
    */

    bool SendCharacterListReuest(int32 userSeq);                                //로비의 캐릭터 리스트에 띄울 정보 요청
    bool SendEnterGameFromLobbyReqeust(const FUserCharacter& EnterCharacter);   //선택한 캐릭터 입장
    bool SendCharacterDeleteRequest(const FUserCharacter& DeleteCharacter);     //선택한 캐릭터 삭제
    bool SendCreateCharacterRequest(const FText NewCharacterName, int32 NewCharacterID);    //캐릭터 생성

    /*
        InGame
    */

    /*
             Info
                        */

    bool SendServerRequest();

    bool SendNPCInfoPacket();

    bool SendEnterPacket(int32 userSeq); //게임 입장 패킷

    bool SendMapInfoRequest(int64 channelId);

    bool SendPlayerPacket();

    bool SendStatusPacket();


    /*
             Item
                        */

    bool SendInventoryPacket();

    bool SendEquipChangePacket(const FItemData& ItemData);      //아이템 장착 패킷.

    bool SendUnEquipChangePacket(const FItemData& ItemData);    //아이템 해제 패킷.

    bool SendAddItemPacket(int64 itemId, int32 value); // 아이템 획득 패킷

    /*
            Action
                        */

    bool SendAttackPacket(FAttackResult attackResult);

    bool SendMovePacket(FVector vector, int64 mapid, int64 channelid);

    /*
            Skill
                        */
    
    bool SendGetSkillPacket();

    bool SendChangeSkillPacket(const FSkillData* SkillData, int skillIdx); //스킬 퀵 슬롯 변경

    bool SendAddSkillPacket(int skillSeq);
    
    /* 
            Shop
                        */

    bool SendBuyPacket(int itemSeq, int shopSeq, int quantity); // 상점 구매 패킷

    bool SendSellPacket(int64 itemId, int shopSeq, int quantity); // 상점 판매 패킷

    /*
            Quest
                        */

    bool SendUserQuestPacket();

    bool SendQuestAddPacket(int npcSeq, int questSeq); // 퀘스트 추가 패킷

    bool SendQuestCheckPacket(int questSeq); // 퀘스트 상태 체크 패킷

    bool SendQuestCompletePacket(int questSeq); // 퀘스트 완료 패킷

    /*
            Dungeon
                        */

    bool SendMatchMaking(int64 mapId);

    /*
            Party
                        */

    bool SendCreateParty();

    bool SendJoinParty(int partyId);

    bool SendLeaveParty(int partyId);


    /*
            Cheat
                        */

    bool SendCreateItemCheatPacket(int32 Seq);

    bool SendCreateSkillCheatPacket(int32 Seq);

    bool SendCreateMonsterCheatPacket(int32 Seq);



    void SetUserSeq(int32 userSeq);
    void SetPlayerSeq(int32 playerSeq);
    void SetMapId(int64 mapId);

    int32 GetUserSeq() { return UserSeq; }
    int32 GetPlayerSeq() { return PlayerSeq; }
    int64 GetMapId() { return MapId; }

private:
    FSocket* MainServerSocket;
    FSocket* MonsterServerSocket;
    FSocket* LobbyServerSocket;
    TSharedPtr<FNetworkReceiver> MainServerReceiver;
    TSharedPtr<FNetworkReceiver> MonsterServerReceiver;
    TSharedPtr<FNetworkReceiver> LobbyServerReceiver;
    FRunnableThread* MainServerThread;
    FRunnableThread* MonsterServerThread;
    FRunnableThread* LobbyServerThread;
    LoadBalancerClient* LoadBalancer;
    UPROPERTY()
    int32 PlayerSeq;
    UPROPERTY()
    int32 UserSeq;
    UPROPERTY()
    int64 MapId;

  

 

};

#define SEND_PACKET(Packet) \
    do { \
        TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(Packet); \
        bool bSuccess = SendToMainSocket(sendBuffer); \
        if (!bSuccess) { \
            UE_LOG(LogTemp, Log, TEXT("%s 패킷 송신 실패"), *FString(UTF8_TO_TCHAR(#Packet))); \
        } else { \
            UE_LOG(LogTemp, Log, TEXT("%s 패킷 송신 성공"), *FString(UTF8_TO_TCHAR(#Packet))); \
        } \
        return bSuccess;\
    } while (0)

