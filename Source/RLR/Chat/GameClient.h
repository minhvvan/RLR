// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Windows/AllowWindowsPlatformTypes.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include "Windows/HideWindowsPlatformTypes.h"
#include "GameFramework/Actor.h"
#include <Networking.h>
#include "../Network/ClientPacketHandler.h"
#include "../Utils/PacketUtils.h"
#include "../Network/FNetworkReceiver.h"
#include "GameClient.generated.h"
class APlayerCharacter;

UCLASS()
class RLR_API AGameClient : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AGameClient();
protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    bool SendLoginPacket(const FString& playerId);
    bool SendMovePacket(int32 playerSeq, float NewX, float NewY);
    bool SendInventoryPacket(int32 playerSeq);
    void CloseConnection();
    bool InitializeSocket(const FString& serverAddress, int32 port);
    bool ReceiveData(uint8* buffer, int32 bufferSize);
    APlayerCharacter* FindPlayerCharacterBySeq(int32_t playerSeq, float newX, float newY);
    APlayerCharacter* SpawnNewPlayerCharacter(int32_t playerSeq, float newX, float newY);
    
    void ProcessMoveResponse(const char* data);
    void ProcessInventoryResponse(const char* data, int32 dataSize);
    
    void ProcessLoginResponse(const char* data);

private:
    TSharedPtr<PacketSession> Session;
    FRunnableThread* Thread;
    FThreadSafeCounter StopTaskCounter;
    SOCKET clientSocket;
    FSocket* socket;
    TSharedPtr<FInternetAddr> remoteAddress;
    APlayerCharacter* myPlayerCharacter;
    UPROPERTY(EditDefaultsOnly, Category = "Player")
    TSubclassOf<APlayerCharacter> playerCharacterClass;
    FNetworkReceiver* networkReceiver;
};
