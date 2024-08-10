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
    void ConnectToLobbyServer(const FString& ServerAddress, int32 Port);
    UFUNCTION(BlueprintCallable)
    void ConnectToMainServer(const FString& ServerAddress, int32 Port);
    UFUNCTION(BlueprintCallable)
    void ConnectToMonsterServer(const FString& ServerAddress, int32 Port);
    UFUNCTION(BlueprintCallable)
    void Update();

    bool SendToMainSocket(TSharedPtr<SendBuffer> sendBuffer);
    bool SendToMonsterSocket(TSharedPtr<SendBuffer> sendBuffer);

    bool SendToLobbySocket(TSharedPtr<SendBuffer> sendBuffer);

    bool SendMapInfoRequest(int64 mapId, int64 channelId);
    bool SendPlayerPacket(int32 playerSeq);
    bool SendStatusPacket(int32 userSeq);

    bool SendInventoryPacket(int32 userSeq);

    bool SendAttackPacket(FAttackResult attackResult);

    bool SendGetSkillPacket(int userSeq);

    bool SendChangeSkillPacket(const FSkillData* SkillData, int userSeq, int skillIdx);

    bool SendServerRequest(int userSeq);

    bool SendMovePacket(int32 userSeq, FVector vector, int64 mapid, int64 channelid);

    bool SendNPCInfoPacket(int64 mapId);

    bool SendUserQuestPacket(int userSeq);

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
};
