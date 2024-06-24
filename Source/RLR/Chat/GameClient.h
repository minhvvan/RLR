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
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

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
    SOCKET clientSocket;
    FSocket* socket;
    TSharedPtr<FInternetAddr> remoteAddress;
    APlayerCharacter* myPlayerCharacter;
    UPROPERTY(EditDefaultsOnly, Category = "Player")
    TSubclassOf<APlayerCharacter> playerCharacterClass;
};

enum PacketType : uint8
{
    // 이동 관련 패킷
    MOVE_REQUEST = 1,
    MOVE_RESPONSE = 2,

    // 상태 관련 패킷
    STATUS_REQUEST = 3,
    STATUS_RESPONSE = 4,

    // 인벤토리 관련 패킷
    INVENTORY_REQUEST = 5,
    INVENTORY_RESPONSE = 6,

    // 아이템 관련 패킷
    ITEM_ADD_REQUEST = 7,
    ITEM_ADD_RESPONSE = 8,
    ITEM_USE_REQUEST = 9,
    ITEM_USE_RESPONSE = 10,

    // 장착 관련 패킷
    ITEM_EQUIP_REQUEST = 11,
    ITEM_EQUIP_RESPONSE = 12,
    ITEM_UNEQUIP_REQUEST = 13,
    ITEM_UNEQUIP_RESPONSE = 14,

    // 기타 패킷 타입들
    CHAT_MESSAGE = 15,
    CHAT_RESPONSE = 16,
    LOGIN_REQUEST = 17,
    LOGIN_RESPONSE = 18,
    LOGOUT_REQUEST = 19,
    LOGOUT_RESPONSE = 20,

    // 상태 업데이트
    HEALTH_UPDATE = 21,
    MANA_UPDATE = 22,
    EXPERIENCE_UPDATE = 23,

    // 파티 및 친구 관련 패킷
    PARTY_INVITE = 24,
    PARTY_INVITE_RESPONSE = 25,
    FRIEND_REQUEST = 26,
    FRIEND_REQUEST_RESPONSE = 27,

    // 퀘스트 관련 패킷
    QUEST_START = 28,
    QUEST_UPDATE = 29,
    QUEST_COMPLETE = 30,

    // 거래 관련 패킷
    TRADE_REQUEST = 31,
    TRADE_RESPONSE = 32,
    TRADE_COMPLETE = 33,

    // 스킬 관련 패킷
    SKILL_USE_REQUEST = 34,
    SKILL_USE_RESPONSE = 35,

    // 기타 패킷 타입들
    PING = 36,
    PONG = 37,

    // 로그 관련 패킷
    SERVER_LOG = 38,
    CLIENT_LOG = 39
};
template<typename T>
inline void Serialize(const T& data, char*& buffer) {
    std::memcpy(buffer, &data, sizeof(T));
    buffer += sizeof(T);
}

template<typename T>
inline void Deserialize(T& data, const char*& buffer) {
    std::memcpy(&data, buffer, sizeof(T));
    buffer += sizeof(T);
}

template<>
inline void Serialize<std::string>(const std::string& data, char*& buffer) {
    int32_t length = static_cast<int32_t>(data.size());
    Serialize(length, buffer);
    std::memcpy(buffer, data.c_str(), length);
    buffer += length;
}

template<>
inline void Deserialize<std::string>(std::string& data, const char*& buffer) {
    int32_t length;
    Deserialize(length, buffer);
    data.assign(buffer, length);
    buffer += length;
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

struct LoginRequestPacket {
    uint8_t packetType = LOGIN_REQUEST;
    char playerId[50];

    void Serialize(char* buffer) const {
        char* bufPtr = buffer;
        std::memcpy(bufPtr, this, sizeof(LoginRequestPacket));
    }

    static LoginRequestPacket Deserialize(const char* buffer) {
        LoginRequestPacket packet;
        std::memcpy(&packet, buffer, sizeof(LoginRequestPacket));
        return packet;
    }
};
struct LoginResponsePacket {
    uint8_t packetType = LOGIN_RESPONSE;
    bool success;
    char gameServerAddress[50];
    int gameServerPort;

    void Serialize(char* buffer) const {
        char* bufPtr = buffer;
        ::Serialize(*this, bufPtr);
        ::Serialize(success, bufPtr);
        ::Serialize(gameServerAddress, bufPtr);
        ::Serialize(gameServerPort, bufPtr);
    }

    static LoginResponsePacket Deserialize(const char* buffer) {
        LoginResponsePacket packet;
        const char* bufPtr = buffer;
        ::Deserialize(packet.packetType, bufPtr);
        ::Deserialize(packet.success, bufPtr);
        ::Deserialize(packet.gameServerAddress, bufPtr);
        ::Deserialize(packet.gameServerPort, bufPtr);
        return packet;
    }
};

struct InventoryRequestPacket {
    uint8_t packetType = INVENTORY_REQUEST;
    int32_t playerSeq;
    void Serialize(char* buffer) const {
        char* bufPtr = buffer;
        ::Serialize(*this, bufPtr);
    }

    static InventoryRequestPacket Deserialize(const char* buffer) {
        InventoryRequestPacket packet;
        const char* bufPtr = buffer;
        ::Deserialize(packet, bufPtr);
        return packet;
    }
};
struct InventoryResponsePacket {
    uint8_t packetType = INVENTORY_RESPONSE;
    int32_t playerSeq;
    int32_t itemCount;
    struct ItemData {
        int itemSeq;
        int itemValue;
        int itemMax;
        char itemType[50];
        long itemId;
        int itemSlotIdx;

        void Serialize(char*& buffer) const {
            ::Serialize(itemSeq, buffer);
            ::Serialize(itemValue, buffer);
            ::Serialize(itemMax, buffer);
            ::Serialize(itemType, buffer);
            ::Serialize(itemId, buffer);
            ::Serialize(itemSlotIdx, buffer);
        }

        void Deserialize(const char*& buffer) {
            ::Deserialize(itemSeq, buffer);
            ::Deserialize(itemValue, buffer);
            ::Deserialize(itemMax, buffer);
            ::Deserialize(itemType, buffer);
            ::Deserialize(itemId, buffer);
            ::Deserialize(itemSlotIdx, buffer);
        }
    } items[100];

    void Serialize(char* buffer) const {
        char* bufPtr = buffer;
        
        ::Serialize(packetType, bufPtr);
        ::Serialize(playerSeq, bufPtr);
        ::Serialize(itemCount, bufPtr);
        for (int i = 0; i < itemCount && i < 100; ++i) {
           
            ::Serialize(items[i].itemSeq, bufPtr);
            ::Serialize(items[i].itemValue, bufPtr);
            ::Serialize(items[i].itemMax, bufPtr);
            ::Serialize(items[i].itemId, bufPtr);
            ::Serialize(items[i].itemSlotIdx, bufPtr);
        }
    }

    static InventoryResponsePacket Deserialize(const char* buffer) {
        InventoryResponsePacket packet;
        const char* bufPtr = buffer;
        ::Deserialize(packet.packetType, bufPtr);
        ::Deserialize(packet.playerSeq, bufPtr);
        ::Deserialize(packet.itemCount, bufPtr);
      
        for (int i = 0; i < packet.itemCount && i < 100; ++i) {
            ::Deserialize(packet.items[i].itemSeq, bufPtr);
            ::Deserialize(packet.items[i].itemValue, bufPtr);
            ::Deserialize(packet.items[i].itemMax, bufPtr);
            ::Deserialize(packet.items[i].itemId, bufPtr);
            ::Deserialize(packet.items[i].itemSlotIdx, bufPtr);
      
        }
        return packet;
    }
};
#pragma pack(pop)