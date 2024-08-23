#pragma once

#include "CoreMinimal.h"
#include "Network/Proto/Packet.pb.h"
#include "Network/Proto/Skill.pb.h"
#include "Network/Proto/NPC.pb.h"
#include "Network/Proto/Item.pb.h"
#include <functional>
#include <memory>
#include "Network/Buffer.h"
#include "Network/Proto/Drop.pb.h"
#include "Network/Proto/Item.pb.h"
#include "Network/Proto/Monster.pb.h"
#include "Network/Proto/Lobby.pb.h"
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
    PKT_SERVER_REQUEST = 1203,
    PKT_CHANNEL_REQUEST = 1211,
    PKT_CHANNEL_RESPONSE = 1212,
    // Add status Packet types
    PKT_STATUS_REQUEST = 1301,
    PKT_STATUS_RESPONSE = 1302,
    // Add inventory packet types
    PKT_INVENTORY_REQUEST = 1311,
    PKT_INVENTORY_RESPONSE = 1312,
    PKT_GET_SKILL_REQUEST = 1321,
    PKT_GET_SKILL_RESPONSE = 1322,
    PKT_SKILL_CHANGE_REQUEST = 1331,
    PKT_SKILL_CHANGE_RESPONSE = 1332,
    PKT_EQUIP_INFO_REQUEST = 1341,
    PKT_EQUIP_INFO_RESPONSE = 1342,
    PKT_EQUIP_CHANGE_REQUEST = 1351,
    PKT_EQUIP_CHANGE_RESPONSE = 1352,
    PKT_NPC_INFO_REQUEST = 1361,
    PKT_NPC_INFO_RESPONSE = 1362,
    PKT_USER_QUEST_REQUEST = 1371,
    PKT_USER_QUEST_RESPONSE = 1372,
    // Add item packet types
    PKT_ITEM_ADD_REQUEST = 1401,
    PKT_ITEM_ADD_RESPONSE = 1402,
    PKT_ITEM_USE_REQUEST = 1403,
    PKT_ITEM_USE_RESPONSE = 1404,

    PKT_ADD_ITEM_REQUEST = 1411,
    PKT_ADD_ITEM_RESPONSE = 1412,

    // Add move packet types
    PKT_MOVE_REQUEST = 1501,
    PKT_MOVE_RESPONSE = 1502,
    PKT_MOVE_BROADCAST = 1503,
    PKT_ATTACK_REQUEST = 1511,
    PKT_ATTACK_RESPONSE = 1512,
    PKT_DAMAGE_REQUSET = 1521,
    PKT_DAMAGE_RESPONSE = 1522,
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
    PKT_MONSTER_RESPAWN_BROADCAST = 1623,
    PKT_MONTSER_MAPINFO_REQUEST = 1631,
    PKT_MONTSER_MAPINFO_RESPONSE = 1632,
    // Add monster attack packet types
    PKT_MONSTER_ATTACK_REQUEST = 1641,
    PKT_MONSTER_ATTACK_RESPONSE = 1642,
    PKT_MONSTER_DIE_REQUEST = 1643,
    PKT_DROP_REQUEST = 1651,
    PKT_DROP_RESPONSE = 1652,
    PKT_EXP_INCREASE_REQUEST = 1653,
    PKT_EXP_INCREASE_RESPONSE = 1654,
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

    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_LoginRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_LOGIN_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_ItemUseRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_ITEM_USE_RESPONSE); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_StatusRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_STATUS_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_CharacterRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_CHARACTER_REQUSET); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_InventoryRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_INVENTORY_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_MoveRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_MOVE_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_MonsterMoveResponsePacket& pkt) { return MakeSendBuffer(pkt, PKT_MONSTER_MOVE_RESPONSE); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_MapMonsterInfoRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_MONTSER_MAPINFO_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_EnterGamePacket& pkt) { return MakeSendBuffer(pkt, PKT_ENTER_GAME_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_AttackRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_ATTACK_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_GetSkillRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_GET_SKILL_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_SkillChangeRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_SKILL_CHANGE_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_ServerReqeustPacket& pkt) { return MakeSendBuffer(pkt, PKT_SERVER_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_UserQuestInfoRequest& pkt) { return MakeSendBuffer(pkt, PKT_USER_QUEST_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_NPCInfoRequest& pkt) { return MakeSendBuffer(pkt, PKT_NPC_INFO_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_EquipInfoRequest& pkt) { return MakeSendBuffer(pkt, PKT_EQUIP_INFO_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_EquipChangeRequest& pkt) { return MakeSendBuffer(pkt, PKT_EQUIP_CHANGE_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_AddItemRequest& pkt) { return MakeSendBuffer(pkt, PKT_ADD_ITEM_REQUEST); }

    



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
