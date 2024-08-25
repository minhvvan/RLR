#pragma once

#include "CoreMinimal.h"
#include <Network/Buffer.h>
#include "Subsystems/GameInstanceSubsystem.h"
#include "RLRStruct.h"
#include "NetworkManager.generated.h"


class FNetworkReceiver;
class LoadBalancerClient;

UCLASS()
class RLR_API UNetworkManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    void Initialize(int64 mapid);
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

    bool SendMapInfoRequest(int64 channelId);
    bool SendPlayerPacket();
    bool SendStatusPacket();

    bool SendInventoryPacket();

    //Item.Proto
    bool SendEquipChangePacket(const FItemData& ItemData);      //아이템 장착 패킷.
    bool SendUnEquipChangePacket(const FItemData& ItemData);    //아이템 해제 패킷.
    //Item.Proto End

    bool SendAttackPacket(FAttackResult attackResult);

    //Skill.Proto
    bool SendGetSkillPacket();
    bool SendChangeSkillPacket(const FSkillData* SkillData, int skillIdx); //스킬 퀵 슬롯 변경
    //Skill.Proto End

    bool SendServerRequest();

    bool SendMovePacket(FVector vector, int64 mapid, int64 channelid);

    bool SendNPCInfoPacket();

    bool SendUserQuestPacket();

    bool SendEnterPacket(int32 userSeq); //게임 입장 패킷

    bool SendAddItemPacket(int64 itemId, int32 value); // 아이템 획득 패킷

    //Cheat.Proto <-- 만들어주세요.
    bool SendCreateItemCheatPacket(int32 Seq);
    bool SendCreateSkillCheatPacket(int32 Seq);
    bool SendCreateMonsterCheatPacket(int32 Seq);

    //Cheat.Proto End

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