#pragma once

#include "CoreMinimal.h"
#include <Network/Buffer.h>
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager/GameManager.h"
#include "RLRStruct.h"

#include "Structs/UtilStructs.h"
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
    bool ConnectToLoginServer(const FString& serverAddress, int32 port);
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

    bool SendCharacterListReuest(int32 playerSeq);                                //로비의 캐릭터 리스트에 띄울 정보 요청
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
    bool SendActionPacket(int32 userSeq, int actionSeq);
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
    bool SendRequestParty(int otherSeq);
    bool SendExileParty(int otherSeq);
    bool SendJoinParty(int partyId);
    bool SendLeaveParty(int partyId);

    /*
            Trade
                        */
    bool SendTradeUserRequest(int32 TargetUserSeq);  //거래 요청 보내기
    bool SendTradeStartReqeust(int32 TargetUserSeq); //거래 요청 수락하기
    bool SendTradeAddItemReqeust(const FItemData& NewTradeItemm, int32 Quantity = 1); //개인 거래에 새로운 아이템 추가하기 패킷
    bool SendTradeAddGoodReqeust(int32 Amount);    //개인 거래에 재화 추가하기
    bool SendTradeLockRequest();   //거래 잠금
    bool SendTradeCancelReqeust(); //거래 취소

    /*
            Cheat
                        */

    bool SendCreateItemCheatPacket(int32 Seq);

    bool SendCreateSkillCheatPacket(int32 Seq);

    bool SendCreateMonsterCheatPacket(int32 Seq);


    /*
            Post
                        */

    bool SendPostRequest(FPostResult post);

    bool SendPostGetRequest();

    bool SendPostRemoveRequest(FPostResult post);

    bool SendPostReadRequest(FPostResult post);

    bool SendPostReceivedRequest(FPostResult post);


    /*
          Friend
                      */
    bool SendInfoFriend();

    bool SendAddFriend(FString friendName);

    bool SendRequestFriend(FString friendName);

    bool SendRemoveFriend(int userSeq);

    bool SendCreateFriendGroup(string& groupName);

    bool SendRemoveFriendGroup(int groupSeq);

    bool SendMoveFriendInGroup(int friendSeq, int groupSeq);

    bool SendMoveFriendGroup(int groupSeq1, int groupSeq2);

    /*
           Guild
                     */
    bool SendInfoGuild();

    bool SendAddGuild(int userSeq, int guildSeq);

    bool SendRemoveGuild(int userSeq, int guildSeq);

    bool SendInviteGuild(int userSeq, int guildSeq);

    bool SendAcceptGuild(int guildSeq);

    bool SendCreateGuild();

    bool SendDeleteGuild(int guildSeq);

    bool SendChangeNameGuild(int guildSeq, FText guildName);

    bool SendChangeRankGuild(int userSeq, int guildSeq, int guildRank);

    /*
         Community
                     */

    bool SendOtherStatus(int userSeq);

    bool SendListCommunity(int communityType);

    bool SendEnterCommunity(int communitySeq);

    bool SendAcceptCommunity(int userSeq, int communitySeq);

    bool SendInviteCommunity(FText userName,int communitySeq);

    bool SendExitCommunity(int communitySeq);

    bool SendCreateCommunity(FText title,int communityType);

    bool SendKickCommunity(int userSeq, int communitySeq);

    bool SendContentCommunity(int communityKey, int communitySeq);
    bool SendCancelContent(int communitySeq);
    bool SendAcceptContent(int communitySeq);
    /*
            Map
                     */
    bool SendContentMap(int64 mapId);

    bool SendMoveMap();



private:
    FSocket* LoginServerSocket;
    FSocket* MainServerSocket;
    FSocket* MonsterServerSocket;
    FSocket* LobbyServerSocket;
    TSharedPtr<FNetworkReceiver> MainServerReceiver;
    TSharedPtr<FNetworkReceiver> MonsterServerReceiver;
    TSharedPtr<FNetworkReceiver> LobbyServerReceiver;
    TSharedPtr<FNetworkReceiver> LoginServerReceiver;
    FRunnableThread* MainServerThread;
    FRunnableThread* MonsterServerThread;
    FRunnableThread* LobbyServerThread;
    FRunnableThread* LoginServerThread;
    LoadBalancerClient* LoadBalancer;
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

