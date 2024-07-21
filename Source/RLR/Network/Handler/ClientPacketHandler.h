#pragma once

#include "CoreMinimal.h"
#include "Network/Proto/Packet.pb.h"
#include <functional>
#include <memory>
#include "Network/Buffer.h"
//#include "CommunityPacketHandler.h"    TODO : 중완님 패킷 핸들러 작업 끝나면 적용 후 기존 PacketHandler에 있떤
//#include "InfoPacketHandler.h"
//#include "ItemPacketHandler.h"
//#include "CertificationPacketHandler.h"
//#include "ActionPacketHandler.h"

class PacketSession;

using PacketHandlerFunc = bool(*)(TSharedPtr<PacketSession>&, uint8*, int32);
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum : uint16
{
    // Add login Packet types
    PKT_LOGIN_REQUEST = 1001,
    PKT_LOGIN_RESPONSE = 1002,
    // Add lobby Paket types
    PKT_CHARACTER_REQUSET = 1101,
    PKT_CHARACTER_RESPONSE = 1102,
    //Add loadBalancer Packet types
    PKT_ENTER_GAME_REQUEST = 1201,
    PKT_ENTER_GAME_RESPONSE = 1202,
    // Add status Packet types
    PKT_STATUS_REQUEST = 1301,
    PKT_STATUS_RESPONSE = 1302,
    // Add inventory packet types
    PKT_INVENTORY_REQUEST = 1311,
    PKT_INVENTORY_RESPONSE = 1312,
    // Add item packet types
    PKT_ITEM_ADD_REQUEST = 1401,
    PKT_ITEM_ADD_RESPONSE = 1402,
    PKT_ITEM_USE_REQUEST = 1403,
    PKT_ITEM_USE_RESPONSE = 1404,


    // Add move packet types
    PKT_MOVE_REQUEST = 1501,
    PKT_MOVE_RESPONSE = 1502,
    PKT_MOVE_BROADCAST = 1503,
    PKT_ATTACK_REQUEST = 1511,
    PKT_ATTACK_RESPONSE = 1512,
    // Add monster move packet types
    PKT_MONSTER_MOVE_REQUEST = 1601,
    PKT_MONSTER_MOVE_RESPONSE = 1602,
    PKT_MONSTER_MOVE_BROADCAST = 1603,
    // Add monster status packet types
    PKT_MONSTER_STATUS_UPDATE = 1611,
    PKT_MONSTER_STATUS_UPDATE_RESPONSE = 1612,
    PKT_MONSTER_STATUS_BROADCAST = 1613,
    // Add monster spawn packet types
    PKT_MONSTER_SPAWN_REQUEST = 1621,
    PKT_MONSTER_SPAWN_RESPONSE = 1622,
    PKT_MONTSER_MAPINFO_REQUEST = 1631,
    PKT_MONTSER_MAPINFO_RESPONSE = 1632,
    // Add monster attack packet types
    PKT_MONSTER_ATTACK_REQUEST = 1641,
    PKT_MONSTER_ATTACK_RESPONSE = 1642,
    // Add party packet types
    PKT_CREATE_PARTY_REQUEST = 1701,
    PKT_CREATE_PARTY_RESPONSE = 1702,
    PKT_JOIN_PARTY_REQUEST = 1711,
    PKT_JOIN_PARTY_RESPONSE = 1712,
    PKT_LEAVE_PARTY_REQUEST = 1721,
    PKT_LEAVE_PARTY_RESPONSE = 1722,
    PKT_PARTY_STATUS_UPDATE = 1731
};

// Custom Handlers
bool Handle_INVALID(TSharedPtr<PacketSession>& session, uint8* buffer, int32 len);
// Login Handlers
bool Handle_LOGIN_REQUEST(TSharedPtr<PacketSession>& session, Protocol::LoginRequestPacket& pkt);
bool Handle_LOGIN_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::LoginResponsePacket& pkt);
// Status Handlers
bool Handle_STATUS_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::StatusResponsePacket& pkt);
// Item Handlers
bool Handle_ITEM_ADD_REQUEST(TSharedPtr<PacketSession>& session, Protocol::ItemAddRequestPacket& pkt);
bool Handle_ITEM_USE_REQUEST(TSharedPtr<PacketSession>& session, Protocol::ItemUseRequestPacket& pkt);
// Inventory Handlers
bool Handle_INVENTORY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::InventoryResponsePacket& pkt);
// Move Handlers
bool Handle_MOVE_REQUEST(TSharedPtr<PacketSession>& session, Protocol::MoveRequestPacket& pkt);
bool Handle_MOVE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::MoveResponsePacket& pkt);
bool Handle_MOVE_BROADCAST(TSharedPtr<PacketSession>& session, Protocol::MoveBroadcastPacket& pkt);

bool Handle_MONSTER_MOVE_REQUEST(TSharedPtr<PacketSession>& session, Protocol::MonsterMoveRequestPacket& pkt);
bool Handle_MONSTER_ATTACK_REQUEST(TSharedPtr<PacketSession>& session, Protocol::MonsterAttackRequestPacket& pkt);
// Enter Game Handlers
bool Handle_ENTER_GAME_REQUEST(TSharedPtr<PacketSession>& session, Protocol::EnterGamePacket& pkt);
bool Handle_ENTER_GAME_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::EnterGameResponsePacket& pkt);
bool Handle_MAP_INFO_REQUEST(TSharedPtr<PacketSession>& session, Protocol::MapMonsterInfoRequestPacket& pkt);
bool Handle_MAP_INFO_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::MapMonsterInfoResponsePacket& pkt);
bool Handle_ATTACK_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::AttackResponsePacket& pkt);
bool Handle_CHARACTER_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::CharacterResponsePacket& pkt);
struct PacketHeader
{
    uint16 size;
    uint16 id; // 패킷 ID
};

class PacketSession : public TSharedFromThis<PacketSession>
{
public:
    PacketSession();
    virtual ~PacketSession();

protected:
    virtual int32 OnRecv(uint8* buffer, int32 len);
    virtual void OnRecvPacket(uint8* buffer, int32 len) PURE_VIRTUAL(PacketSession::OnRecvPacket, );
};

class ClientPacketHandler
{
public:
    static void Init();

    bool HandlePacket(TSharedPtr<PacketSession>& session, uint8* buffer, int32 len);

    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::LoginRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_LOGIN_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::LoginResponsePacket& pkt) { return MakeSendBuffer(pkt, PKT_LOGIN_RESPONSE); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::ItemAddResponsePacket& pkt) { return MakeSendBuffer(pkt, PKT_ITEM_ADD_RESPONSE); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::ItemUseResponsePacket& pkt) { return MakeSendBuffer(pkt, PKT_ITEM_USE_RESPONSE); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::StatusRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_STATUS_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CharacterRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_CHARACTER_REQUSET); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::InventoryRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_INVENTORY_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::InventoryResponsePacket& pkt) { return MakeSendBuffer(pkt, PKT_INVENTORY_RESPONSE); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::MoveResponsePacket& pkt) { return MakeSendBuffer(pkt, PKT_MOVE_RESPONSE); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::MoveBroadcastPacket& pkt) { return MakeSendBuffer(pkt, PKT_MOVE_BROADCAST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::MonsterMoveResponsePacket& pkt) { return MakeSendBuffer(pkt, PKT_MONSTER_MOVE_RESPONSE); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::MonsterAttackResponsePacket& pkt) { return MakeSendBuffer(pkt, PKT_MONSTER_ATTACK_RESPONSE); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::MapMonsterInfoRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_MONTSER_MAPINFO_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::EnterGamePacket& pkt) { return MakeSendBuffer(pkt, PKT_ENTER_GAME_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::EnterGameResponsePacket& pkt) { return MakeSendBuffer(pkt, PKT_ENTER_GAME_RESPONSE); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::AttackRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_ATTACK_REQUEST); }

public:
    template<typename PacketType>
    bool HandlePacket(bool(*func)(TSharedPtr<PacketSession>&, PacketType&), TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
    {
        PacketType pkt;
        if (!pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)))
            return false;

        return func(session, pkt);
    }

    template<typename T>
    static TSharedPtr<SendBuffer> MakeSendBuffer(T& pkt, uint16 pktId)
    {
        const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
        const uint16 packetSize = dataSize + sizeof(PacketHeader);
        TSharedPtr<SendBuffer> sendBuffer = MakeShared<SendBuffer>(packetSize);
        PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->GetBuffer());
        header->size = packetSize;
        header->id = pktId;
        if (!pkt.SerializeToArray(&header[1], dataSize))
            return nullptr;
        sendBuffer->Close(packetSize);

        return sendBuffer;
    }
};
