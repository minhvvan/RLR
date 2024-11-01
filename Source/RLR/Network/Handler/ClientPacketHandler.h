#pragma once

#include "CoreMinimal.h"
#include "Network/Proto/Packet.pb.h"
#include "Network/Proto/Skill.pb.h"
#include "Network/Proto/NPC.pb.h"
#include "Network/Proto/Item.pb.h"
#include "Network/Proto/Cheat.pb.h"
#include "Network/Proto/User.pb.h"
#include <functional>
#include <memory>
#include "Network/Buffer.h"
#include "Network/Proto/Drop.pb.h"
#include "Network/Proto/Item.pb.h"
#include "Network/Proto/Monster.pb.h"
#include "Network/Proto/Lobby.pb.h"
#include "Network/Proto/Shop.pb.h"
#include "Network/Proto/Dungeon.pb.h"
#include "Network/Proto/Action.pb.h"
#include "Network/Proto/Post.pb.h"
#include "Network/Proto/Trade.pb.h"
#include "Network/Proto/Friend.pb.h"
#include "Network/Proto/Good.pb.h"
#include "Network/Proto/Guild.pb.h"
#include "Network/Proto/Map.pb.h"
#include "Network/Proto/Community.pb.h"

class PacketMessage;
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
    PKT_USER_SPAWN_REQUEST = 1303,
    PKT_USER_SPAWN_RESPONSE = 1304,
    // Add inventory packet types
    PKT_INVENTORY_REQUEST = 1311,
    PKT_INVENTORY_RESPONSE = 1312,
    PKT_GET_SKILL_REQUEST = 1321,
    PKT_GET_SKILL_RESPONSE = 1322,
    PKT_SKILL_CHANGE_REQUEST = 1331,
    PKT_SKILL_CHANGE_RESPONSE = 1332,
    PKT_SKILL_ADD_REQUEST = 1333,
    PKT_SKILL_ADD_RESPONSE = 1334,
    PKT_EQUIP_INFO_REQUEST = 1341,
    PKT_EQUIP_INFO_RESPONSE = 1342,
    PKT_EQUIP_CHANGE_REQUEST = 1351,
    PKT_EQUIP_CHANGE_RESPONSE = 1352,
    PKT_NPC_INFO_REQUEST = 1361,
    PKT_NPC_INFO_RESPONSE = 1362,
    PKT_USER_QUEST_REQUEST = 1371,
    PKT_USER_QUEST_RESPONSE = 1372,
    PKT_QUEST_ADD_REQUEST = 1373,
    PKT_QUEST_ADD_RESPONSE = 1374,
    PKT_QUEST_CHECK_REQUEST = 1375,
    PKT_QUEST_CHECK_RESPONSE = 1376,
    PKT_QUEST_COMPLETE_REQUEST = 1377,
    PKT_QUEST_COMPLETE_RESPONSE = 1378,
    // Add item packet types
    PKT_ITEM_ADD_REQUEST = 1401,
    PKT_ITEM_ADD_RESPONSE = 1402,
    PKT_ITEM_USE_REQUEST = 1403,
    PKT_ITEM_USE_RESPONSE = 1404,
    PKT_ITEM_QUICK_CHANGE_REQUEST = 1405,
    PKT_ITEM_QUICK_CHANGE_RESPONSE = 1406,
    PKT_ADD_ITEM_REQUEST = 1411,
    PKT_ADD_ITEM_RESPONSE = 1412,
    PKT_SHOP_BUY_REQUEST = 1421,
    PKT_SHOP_BUY_RESPONSE = 1422,
    PKT_SHOP_SELL_REQUEST = 1423,
    PKT_SHOP_SELL_RESPONSE = 1424,
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
    PKT_REQUEST_PARTY_REQUEST = 1713,
    PKT_REQUEST_PARTY_RESPONSE = 1714,
    PKT_LEAVE_PARTY_REQUEST = 1721,
    PKT_LEAVE_PARTY_RESPONSE = 1722,
    PKT_EXILE_PARTY_REQUEST = 1723,
    PKT_EXILE_PARTY_RESPONSE = 1724,
    PKT_PARTY_STATUS_UPDATE = 1731,
    PKT_PARTY_MAP_INFO_REQUEST = 1741,
    // Add friend packet types
    PKT_FRIEND_INFO_REQUEST = 1751,
    PKT_FRIEND_INFO_RESPONSE = 1752,
    PKT_FRIEND_CONNECT_REQUEST = 1753,
    PKT_FRIEND_CONNECT_RESPONSE = 1754,
    PKT_ADD_FRIEND_REQUEST = 1761,
    PKT_ADD_FRIEND_RESPONSE = 1762,
    PKT_REMOVE_FRIEND_REQUEST = 1763,
    PKT_REMOVE_FRIEND_RESPONSE = 1764,
    PKT_REQUEST_FRIEND_REQUEST = 1765,
    PKT_REQUEST_FRIEND_RESPONSE = 1766,
    PKT_CREATE_FRIEND_GROUP_REQUEST = 1771,
    PKT_CREATE_FRIEND_GROUP_RESPONSE = 1772,
    PKT_REMOVE_FRIEND_GROUP_REQUEST = 1773,
    PKT_REMOVE_FRIEND_GROUP_RESPONSE = 1774,
    PKT_MOVE_FRIEND_IN_GROUP_REQUEST = 1781,
    PKT_MOVE_FRIEND_IN_GROUP_RESPONSE = 1782,
    PKT_MOVE_FRIEND_GROUP_REQUEST = 1783,
    PKT_MOVE_FRIEND_GROUP_RESPONSE = 1784,
    // Add Guild packet types
    PKT_GUILD_INFO_REQUEST = 1801,
    PKT_GUILD_INFO_RESPONSE = 1802,
    PKT_ADD_GUILD_REQUEST = 1803,
    PKT_ADD_GUILD_RESPONSE = 1804,
    PKT_REMOVE_GUILD_REQUEST = 1805,
    PKT_REMOVE_GUILD_RESPONSE = 1806,
    PKT_CREATE_GUILD_REQUEST = 1807,
    PKT_CREATE_GUILD_RESPONSE = 1808,
    PKT_DELETE_GUILD_REQUEST = 1810,
    PKT_DELETE_GUILD_RESPONSE = 1811,
    PKT_CHANGE_NAME_GUILD_REQUEST = 1812,
    PKT_CHANGE_NAME_GUILD_RESPONSE = 1813,
    PKT_CHANGE_RANK_GUILD_REQUEST = 1814,
    PKT_CHANGE_RANK_GUILD_RESPONSE = 1815,
    PKT_GUILD_CONNECT_RESPONSE = 1816,
    PKT_INVITE_GUILD_REQUEST = 1817,
    PKT_INVITE_GUILD_RESPONSE = 1818,
    PKT_ACCEPT_GUILD_REQUEST = 1819,
    PKT_ACCEPT_GUILD_RESPONSE = 1820,
    // Add Cheat Packet types
    PKT_CHEAT_ITEM_REQUEST = 1901,
    PKT_CHEAT_SKILL_REQUEST = 1902,
    PKT_CHEAT_MONSTER_REQUEST = 1903,

    PKT_MATCH_MAKING_REQUEST = 2001,

    // Action
    PKT_ACTION_REQUEST = 2101,
    PKT_ACTION_RESPONSE = 2102,

    // Add Post Packet types
    PKT_POST_SEND_REQUEST = 3001,
    PKT_POST_SEND_RESPONSE = 3002,

    PKT_POST_READ_REQUEST = 3003,
    PKT_POST_READ_RESPONSE = 3004,

    PKT_POST_RECEIVED_REQUEST = 3005,
    PKT_POST_RECEIVED_RESPONSE = 3006,
    PKT_POST_GET_REQUEST = 3007,
    PKT_POST_GET_RESPONSE = 3008,

    PKT_POST_REMOVE_REQUEST = 3009,
    // Add Trade Packet types
    PKT_TRADE_USER_REQUEST = 3011,
    PKT_TRADE_USER_RESPONSE = 3012,

    PKT_TRADE_START_REQUEST = 3013,
    PKT_TRADE_START_RESPONSE = 3014,

    PKT_TRADE_ADD_ITEM_REQUEST = 3015,
    PKT_TRADE_ADD_GOOD_REQUEST = 3016,

    PKT_TRADE_STATE_RESPONSE = 3017,
    PKT_TRADE_COMPLETE_RESPONSE = 3018,

    PKT_TRADE_LOCK_REQUEST = 3021,
    PKT_TRADE_LOCK_RESPONSE = 3022,

    PKT_TRADE_SUCCESS_REQUEST = 3023,
    PKT_TRADE_SUCCESS_RESPONSE = 3024,

    PKT_TRADE_CANCEL_REQUEST = 3025,
    PKT_TRADE_CANCEL_RESPONSE = 3026,
    // Add Community Packet types
    PKT_OTHER_STATUS_REQUEST = 3101,
    PKT_OTHER_STATUS_RESPONSE = 3102,
    PKT_REPORT_REQUEST = 3111,
    PKT_COMMUNITY_LIST_REQUEST = 3121,
    PKT_COMMUNITY_LIST_RESPONSE = 3122,
    PKT_COMMUNITY_ACCEPT_REQUEST = 3123,
    PKT_COMMUNITY_ACCEPT_RESPONSE = 3124,
    PKT_COMMUNITY_INVITE_REQUEST = 3125,
    PKT_COMMUNITY_INVITE_RESPONSE = 3126,
    PKT_COMMUNITY_STATE_RESPONSE = 3127,
    PKT_COMMUNITY_ENTER_REQUEST = 3128,
    PKT_COMMUNITY_EXIT_REQUEST = 3129,
    PKT_COMMUNITY_CREATE_REQUEST = 3130,
    PKT_COMMUNITY_KICK_REQUEST = 3131,
    PKT_COMMUNITY_KICK_RESPONSE = 3132,
    PKT_COMMUNITY_CONTENT_REQUEST = 3133,
    PKT_COMMUNITY_CONTENT_RESPONSE = 3134,
    // Add Content packet types
    PKT_CONTENT_FAIL_RESPONSE = 3141,
    PKT_CONTENT_ACCEPT_REQUEST = 3142,
    PKT_CONTENT_ACCEPT_RESPONSE = 3143,
    PKT_CONTENT_CANCEL_REQUEST = 3144,
    PKT_CONTENT_CANCEL_RESPONSE = 3145,
    // Add Good packet types
    PKT_GOOD_USER_REQUEST = 4001,
    PKT_GOOD_USER_RESPONSE = 4002,
    PKT_GOOD_PLAYER_REQUEST = 4003,
    PKT_GOOD_PLAYER_RESPONSE = 4004,

    // Add Map packet types
    PKT_MAP_MOVE_REQUEST = 5001,
    PKT_MAP_CONTENT_REQUEST = 5002,
    PKT_MAP_RESPONSE = 5003,

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
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_BuyRequest& pkt) { return MakeSendBuffer(pkt, PKT_SHOP_BUY_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_SellRequest& pkt) { return MakeSendBuffer(pkt, PKT_SHOP_SELL_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_QuestAddRequest& pkt) { return MakeSendBuffer(pkt, PKT_QUEST_ADD_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_QuestCheckRequest& pkt) { return MakeSendBuffer(pkt, PKT_QUEST_CHECK_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_QuestCompleteRequest& pkt) { return MakeSendBuffer(pkt, PKT_QUEST_COMPLETE_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_CreateItemCheatPacket& pkt) { return MakeSendBuffer(pkt, PKT_CHEAT_ITEM_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_CreateSkillCheatPacket& pkt) { return MakeSendBuffer(pkt, PKT_CHEAT_SKILL_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_CreateMonsterCheatPacket& pkt) { return MakeSendBuffer(pkt, PKT_CHEAT_MONSTER_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_SkillAddRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_SKILL_ADD_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_MatchMakingRequest& pkt) { return MakeSendBuffer(pkt, PKT_MATCH_MAKING_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_CreatePartyRequest& pkt) { return MakeSendBuffer(pkt, PKT_CREATE_PARTY_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_JoinPartyRequest& pkt) { return MakeSendBuffer(pkt, PKT_JOIN_PARTY_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_LeavePartyRequest& pkt) { return MakeSendBuffer(pkt, PKT_LEAVE_PARTY_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_ExilePartyRequest& pkt) { return MakeSendBuffer(pkt, PKT_EXILE_PARTY_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_RequestPartyRequest& pkt) { return MakeSendBuffer(pkt, PKT_REQUEST_PARTY_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_ActionRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_ACTION_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_PostRequest& pkt) { return MakeSendBuffer(pkt, PKT_POST_SEND_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_PostRead& pkt) { return MakeSendBuffer(pkt, PKT_POST_READ_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_PostGetRequest& pkt) { return MakeSendBuffer(pkt, PKT_POST_GET_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_PostReceived& pkt) { return MakeSendBuffer(pkt, PKT_POST_RECEIVED_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_RemovePostRequest& pkt) { return MakeSendBuffer(pkt, PKT_POST_REMOVE_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_TradeStartRequest& pkt) { return MakeSendBuffer(pkt, PKT_TRADE_START_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_TradeUserRequest& pkt) { return MakeSendBuffer(pkt, PKT_TRADE_USER_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_TradeLockRequest& pkt) { return MakeSendBuffer(pkt, PKT_TRADE_LOCK_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_TradeCancelRequest& pkt) { return MakeSendBuffer(pkt, PKT_TRADE_CANCEL_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_TradeAddItemRequest& pkt) { return MakeSendBuffer(pkt, PKT_TRADE_ADD_ITEM_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_TradeAddGoodRequest& pkt) { return MakeSendBuffer(pkt, PKT_TRADE_ADD_GOOD_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_FriendInfoRequest& pkt) { return MakeSendBuffer(pkt, PKT_FRIEND_INFO_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_RemoveFriendRequest& pkt) { return MakeSendBuffer(pkt, PKT_REMOVE_FRIEND_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_AddFriendRequest& pkt) { return MakeSendBuffer(pkt, PKT_ADD_FRIEND_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_RequestFriendRequest& pkt) { return MakeSendBuffer(pkt, PKT_REQUEST_FRIEND_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_CreateFriendGroupRequest& pkt) { return MakeSendBuffer(pkt, PKT_CREATE_FRIEND_GROUP_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_RemoveFriendGroupRequest& pkt) { return MakeSendBuffer(pkt, PKT_REMOVE_FRIEND_GROUP_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_MoveFriendGroupRequest& pkt) { return MakeSendBuffer(pkt, PKT_MOVE_FRIEND_GROUP_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_MoveFriendInGroupRequest& pkt) { return MakeSendBuffer(pkt, PKT_MOVE_FRIEND_IN_GROUP_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_PlayerGoodRequest& pkt) { return MakeSendBuffer(pkt, PKT_GOOD_PLAYER_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_UserGoodRequest& pkt) { return MakeSendBuffer(pkt, PKT_GOOD_USER_REQUEST); }

    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_GuildInfoRequest& pkt) { return MakeSendBuffer(pkt, PKT_GUILD_INFO_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_GuildAddRequest& pkt) { return MakeSendBuffer(pkt, PKT_ADD_GUILD_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_GuildRemoveRequest& pkt) { return MakeSendBuffer(pkt, PKT_REMOVE_GUILD_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_GuildCreateRequest& pkt) { return MakeSendBuffer(pkt, PKT_CREATE_GUILD_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_GuildDeleteRequest& pkt) { return MakeSendBuffer(pkt, PKT_DELETE_GUILD_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_GuildAcceptRequest& pkt) { return MakeSendBuffer(pkt, PKT_ACCEPT_GUILD_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_GuildInviteRequest& pkt) { return MakeSendBuffer(pkt, PKT_INVITE_GUILD_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_GuildChangeNameRequest& pkt) { return MakeSendBuffer(pkt, PKT_CHANGE_NAME_GUILD_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_GuildChangeRankRequest& pkt) { return MakeSendBuffer(pkt, PKT_CHANGE_RANK_GUILD_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_OtherStatusRequest& pkt) { return MakeSendBuffer(pkt, PKT_OTHER_STATUS_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_CommunityListRequest& pkt) { return MakeSendBuffer(pkt, PKT_COMMUNITY_LIST_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_CommunityAcceptRequest& pkt) { return MakeSendBuffer(pkt, PKT_COMMUNITY_ACCEPT_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_CommunityCreateRequest& pkt) { return MakeSendBuffer(pkt, PKT_COMMUNITY_CREATE_REQUEST); }

    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_CommunityInviteRequest& pkt) { return MakeSendBuffer(pkt, PKT_COMMUNITY_INVITE_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_CommunityKickRequest& pkt) { return MakeSendBuffer(pkt, PKT_COMMUNITY_KICK_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_CommunityExitRequest& pkt) { return MakeSendBuffer(pkt, PKT_COMMUNITY_EXIT_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_CommunityContentRequest& pkt) { return MakeSendBuffer(pkt, PKT_COMMUNITY_CONTENT_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_CommunityEnterRequest& pkt) { return MakeSendBuffer(pkt, PKT_COMMUNITY_ENTER_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_ContentAcceptRequest& pkt) { return MakeSendBuffer(pkt, PKT_CONTENT_ACCEPT_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_ContentCancelRequest& pkt) { return MakeSendBuffer(pkt, PKT_CONTENT_CANCEL_REQUEST); }

    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_MapMoveRequest& pkt) { return MakeSendBuffer(pkt, PKT_MAP_MOVE_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::CS_MapContentRequest& pkt) { return MakeSendBuffer(pkt, PKT_MAP_CONTENT_REQUEST); }
    
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

