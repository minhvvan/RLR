// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Windows/AllowWindowsPlatformTypes.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include "Windows/HideWindowsPlatformTypes.h"
#include "../Player/PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include <Networking.h>
#include "GameClient.generated.h"


UCLASS()
class RLR_API AGameClient : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AGameClient();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    bool SendMovePacket(int32 userSeq, float NewX, float NewY);
    void CloseConnection();
    bool InitializeSocket(const FString& ServerAddress, int32 Port);
    bool ReceiveData(uint8* buffer, int32 bufferSize);
    APlayerCharacter* FindPlayerCharacterBySeq(int32_t userSeq, float newX, float newY);
    APlayerCharacter* SpawnNewPlayerCharacter(int32_t userSeq, float newX, float newY);
    void ProcessMoveResponse(const char* data);

 

private:
    SOCKET ClientSocket;
    FSocket* Socket;
    TSharedPtr<FInternetAddr> RemoteAddress;
    APlayerCharacter* MyPlayerCharacter;
    UPROPERTY(EditDefaultsOnly, Category = "Player")
    TSubclassOf<APlayerCharacter> PlayerCharacterClass; // 추가된 부분
};
enum PacketType : uint8
{
	MOVE_REQUEST = 1,
	MOVE_RESPONSE = 2,
	Whisper,
	Country,
	World,
	Guild,
	Raid,
	Party,
	Continent,
	Nearby
};
template<typename T>
void Serialize(const T& data, char*& buffer) {
    std::memcpy(buffer, &data, sizeof(T));
    buffer += sizeof(T);
}

template<typename T>
void Deserialize(T& data, const char*& buffer) {
    std::memcpy(&data, buffer, sizeof(T));
    buffer += sizeof(T);
}
#pragma pack(push, 1)

struct MoveRequestPacket {
    uint8_t packetType = MOVE_REQUEST;
    int32_t playerSeq;
    float newX;
    float newY;
    void Serialize(char* buffer) const {
        char* bufPtr = buffer;
        ::Serialize(*this, bufPtr);
    }

    static MoveRequestPacket Deserialize(const char* buffer) {
        MoveRequestPacket packet;
        const char* bufPtr = buffer;
        ::Deserialize(packet, bufPtr);
        return packet;
    }
};

struct MoveResponsePacket {
    uint8_t packetType = MOVE_RESPONSE;
    int32_t playerSeq;
    float newX;
    float newY;
    bool success;

 
    void Serialize(char* buffer) const {
        char* bufPtr = buffer;
        ::Serialize(*this, bufPtr);
    }

    static MoveResponsePacket Deserialize(const char* buffer) {
        MoveResponsePacket packet;
        const char* bufPtr = buffer;
        ::Deserialize(packet, bufPtr);
        return packet;
    }
};
#pragma pack(pop)