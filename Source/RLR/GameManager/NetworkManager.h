#pragma once

#include "CoreMinimal.h"
#include <Network/Buffer.h>
#include "Subsystems/GameInstanceSubsystem.h"
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
    void ConnectToMainServer(const FString& ServerAddress, int32 Port);
    UFUNCTION(BlueprintCallable)
    void ConnectToMonsterServer(const FString& ServerAddress, int32 Port);
    UFUNCTION(BlueprintCallable)
    void Update();

    bool SendToMainSocket(TSharedPtr<SendBuffer> sendBuffer);
    bool SendToMonsterSocket(TSharedPtr<SendBuffer> sendBuffer);

private:
    FSocket* MainServerSocket;
    FSocket* MonsterServerSocket;

    TSharedPtr<FNetworkReceiver> MainServerReceiver;
    TSharedPtr<FNetworkReceiver> MonsterServerReceiver;

    FRunnableThread* MainServerThread;
    FRunnableThread* MonsterServerThread;

    LoadBalancerClient* LoadBalancer;
};
