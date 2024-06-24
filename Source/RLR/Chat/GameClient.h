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
#include "../Utils/PacketUtils.h"
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

// STATUS_REQUEST 패킷 구조체
struct StatusRequestPacket {
    uint8_t packetType = STATUS_REQUEST;
    int32_t userId;
};

// STATUS_RESPONSE 패킷 구조체
struct StatusResponsePacket {
    uint8_t packetType = STATUS_RESPONSE;
    int32_t userId;
    int32_t health;
    int32_t mana;
    int32_t experience;
};

// INVENTORY_REQUEST 패킷 구조체
struct InventoryRequestPacket {
    uint8_t packetType = INVENTORY_REQUEST;
    int32_t playerSeq;

    void Serialize(char* buffer) const {
        char* bufPtr = buffer;
        ::Serialize(packetType, bufPtr);
        ::Serialize(playerSeq, bufPtr);
    }

    static InventoryRequestPacket Deserialize(const char* buffer) {
        InventoryRequestPacket packet;
        const char* bufPtr = buffer;
        ::Deserialize(packet.packetType, bufPtr);
        ::Deserialize(packet.playerSeq, bufPtr);
        return packet;
    }
}; struct InventoryResponsePacket {
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
    } items[100];

    void Serialize(char* buffer) const {
        char* bufPtr = buffer;
        ::Serialize(packetType, bufPtr);
        ::Serialize(playerSeq, bufPtr);
        ::Serialize(itemCount, bufPtr);
        for (int i = 0; i < itemCount; ++i) {
            ::Serialize(items[i].itemSeq, bufPtr);
            ::Serialize(items[i].itemValue, bufPtr);
            ::Serialize(items[i].itemMax, bufPtr);
            ::Serialize(items[i].itemType, bufPtr, sizeof(items[i].itemType));
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
        for (int i = 0; i < packet.itemCount; ++i) {
            ::Deserialize(packet.items[i].itemSeq, bufPtr);
            ::Deserialize(packet.items[i].itemValue, bufPtr);
            ::Deserialize(packet.items[i].itemMax, bufPtr);
            ::Deserialize(packet.items[i].itemType, bufPtr, sizeof(packet.items[i].itemType));
            ::Deserialize(packet.items[i].itemId, bufPtr);
            ::Deserialize(packet.items[i].itemSlotIdx, bufPtr);
        }
        return packet;
    }
};
// ITEM_ADD_REQUEST 패킷 구조체
struct ItemAddRequestPacket {
    uint8_t packetType = ITEM_ADD_REQUEST;
    int32_t userId;
    int32_t itemId;
    int32_t quantity;
};

struct LoginRequestPacket {
    uint8_t packetType = LOGIN_REQUEST;
    char playerId[50];

    void Serialize(char* buffer) const {
        char* bufPtr = buffer;
        ::Serialize(packetType, bufPtr);
        ::Serialize(playerId, bufPtr, sizeof(playerId));
    }

    static LoginRequestPacket Deserialize(const char* buffer) {
        LoginRequestPacket packet;
        const char* bufPtr = buffer;
        ::Deserialize(packet.packetType, bufPtr);
        ::Deserialize(packet.playerId, bufPtr, sizeof(packet.playerId));
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
        ::Serialize(packetType, bufPtr);
        ::Serialize(success, bufPtr);
        ::Serialize(gameServerAddress, bufPtr, sizeof(gameServerAddress));
        ::Serialize(gameServerPort, bufPtr);
    }

    static LoginResponsePacket Deserialize(const char* buffer) {
        LoginResponsePacket packet;
        const char* bufPtr = buffer;
        ::Deserialize(packet.packetType, bufPtr);
        ::Deserialize(packet.success, bufPtr);
        ::Deserialize(packet.gameServerAddress, bufPtr, sizeof(packet.gameServerAddress));
        ::Deserialize(packet.gameServerPort, bufPtr);
        return packet;
    }
};
// ITEM_ADD_RESPONSE 패킷 구조체
struct ItemAddResponsePacket {
    uint8_t packetType = ITEM_ADD_RESPONSE;
    int32_t userId;
    int32_t itemId;
    int32_t quantity;
    bool success;
};

// ITEM_USE_REQUEST 패킷 구조체
struct ItemUseRequestPacket {
    uint8_t packetType = ITEM_USE_REQUEST;
    int32_t userId;
    int32_t itemId;
};

// ITEM_USE_RESPONSE 패킷 구조체
struct ItemUseResponsePacket {
    uint8_t packetType = ITEM_USE_RESPONSE;
    int32_t userId;
    int32_t itemId;
    bool success;
};

// ITEM_EQUIP_REQUEST 패킷 구조체
struct ItemEquipRequestPacket {
    uint8_t packetType = ITEM_EQUIP_REQUEST;
    int32_t userId;
    int32_t itemId;
    char equipArea[32];
};

// ITEM_EQUIP_RESPONSE 패킷 구조체
struct ItemEquipResponsePacket {
    uint8_t packetType = ITEM_EQUIP_RESPONSE;
    int32_t userId;
    int32_t itemId;
    char equipArea[32];
    bool success;
};

// ITEM_UNEQUIP_REQUEST 패킷 구조체
struct ItemUnequipRequestPacket {
    uint8_t packetType = ITEM_UNEQUIP_REQUEST;
    int32_t userId;
    int32_t itemId;
};

// ITEM_UNEQUIP_RESPONSE 패킷 구조체
struct ItemUnequipResponsePacket {
    uint8_t packetType = ITEM_UNEQUIP_RESPONSE;
    int32_t userId;
    int32_t itemId;
    bool success;
};

// CHAT_MESSAGE 패킷 구조체
struct ChatMessagePacket {
    uint8_t packetType = CHAT_MESSAGE;
    int32_t userId;
    char message[256];
};

// CHAT_RESPONSE 패킷 구조체
struct ChatResponsePacket {
    uint8_t packetType = CHAT_RESPONSE;
    int32_t userId;
    char message[256];
    bool success;
};


// HEALTH_UPDATE 패킷 구조체
struct HealthUpdatePacket {
    uint8_t packetType = HEALTH_UPDATE;
    int32_t userId;
    int32_t health;
};

// MANA_UPDATE 패킷 구조체
struct ManaUpdatePacket {
    uint8_t packetType = MANA_UPDATE;
    int32_t userId;
    int32_t mana;
};

// EXPERIENCE_UPDATE 패킷 구조체
struct ExperienceUpdatePacket {
    uint8_t packetType = EXPERIENCE_UPDATE;
    int32_t userId;
    int32_t experience;
};

// PARTY_INVITE 패킷 구조체
struct PartyInvitePacket {
    uint8_t packetType = PARTY_INVITE;
    int32_t inviterId;
    int32_t inviteeId;
};

// PARTY_INVITE_RESPONSE 패킷 구조체
struct PartyInviteResponsePacket {
    uint8_t packetType = PARTY_INVITE_RESPONSE;
    int32_t inviterId;
    int32_t inviteeId;
    bool accepted;
};

// FRIEND_REQUEST 패킷 구조체
struct FriendRequestPacket {
    uint8_t packetType = FRIEND_REQUEST;
    int32_t requesterId;
    int32_t requesteeId;
};

// FRIEND_REQUEST_RESPONSE 패킷 구조체
struct FriendRequestResponsePacket {
    uint8_t packetType = FRIEND_REQUEST_RESPONSE;
    int32_t requesterId;
    int32_t requesteeId;
    bool accepted;
};

// QUEST_START 패킷 구조체
struct QuestStartPacket {
    uint8_t packetType = QUEST_START;
    int32_t userId;
    int32_t questId;
};

// QUEST_UPDATE 패킷 구조체
struct QuestUpdatePacket {
    uint8_t packetType = QUEST_UPDATE;
    int32_t userId;
    int32_t questId;
    int32_t progress;
};

// QUEST_COMPLETE 패킷 구조체
struct QuestCompletePacket {
    uint8_t packetType = QUEST_COMPLETE;
    int32_t userId;
    int32_t questId;
};

// TRADE_REQUEST 패킷 구조체
struct TradeRequestPacket {
    uint8_t packetType = TRADE_REQUEST;
    int32_t requesterId;
    int32_t requesteeId;
};

// TRADE_RESPONSE 패킷 구조체
struct TradeResponsePacket {
    uint8_t packetType = TRADE_RESPONSE;
    int32_t requesterId;
    int32_t requesteeId;
    bool accepted;
};

// TRADE_COMPLETE 패킷 구조체
struct TradeCompletePacket {
    uint8_t packetType = TRADE_COMPLETE;
    int32_t userId;
    int32_t itemId;
    int32_t quantity;
};

// SKILL_USE_REQUEST 패킷 구조체
struct SkillUseRequestPacket {
    uint8_t packetType = SKILL_USE_REQUEST;
    int32_t userId;
    int32_t skillId;
};

// SKILL_USE_RESPONSE 패킷 구조체
struct SkillUseResponsePacket {
    uint8_t packetType = SKILL_USE_RESPONSE;
    int32_t userId;
    int32_t skillId;
    bool success;
};

// PING 패킷 구조체
struct PingPacket {
    uint8_t packetType = PING;
};

// PONG 패킷 구조체
struct PongPacket {
    uint8_t packetType = PONG;
};

// SERVER_LOG 패킷 구조체
struct ServerLogPacket {
    uint8_t packetType = SERVER_LOG;
    char logMessage[256];
};

// CLIENT_LOG 패킷 구조체
struct ClientLogPacket {
    uint8_t packetType = CLIENT_LOG;
    char logMessage[256];
};

#pragma pack(pop)
