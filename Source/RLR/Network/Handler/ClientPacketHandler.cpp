#include "ClientPacketHandler.h"
#include "GameManager/GameManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/MonsterManager.h"
#include "Network/Buffer.h"
//UI
#include "UI/MainUI.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/CharacterProfile/CharacterProfile.h"
#include "UI/InGame/CharacterProfile/Equipment/EquipmentUI.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "CertificationPacketHandler.h"
#include "InfoPacketHandler.h"
#include "ItemPacketHandler.h"
#include "CommunityPacketHandler.h"
#include "ActionPacketHandler.h"
#include "PartyPacketHandler.h"
#include "TradePacketHandler.h"
#include "PostPacketHandler.h"
#include "FriendPacketHandler.h"
#include "GuildPacketHandler.h"
#include "MapPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(TSharedPtr<PacketSession>& session, BYTE* buffer, int32 len)
{

    // Handle invalid packet
    return false;
}

void ClientPacketHandler::Init()
{
    for (int32 i = 0; i < UINT16_MAX; i++)
        GPacketHandler[i] = Handle_INVALID;

    static ClientPacketHandler instance;

    
    GPacketHandler[PKT_LOGIN_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_LoginResponsePacket>(&Handle_LOGIN_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_CHARACTER_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_UserResponsePacket>(&Handle_CHARACTER_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_STATUS_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_StatusResponsePacket>(&Handle_STATUS_RESPONSE, session, buffer, len);
        };
    // Add item packet handlers
    GPacketHandler[PKT_ADD_ITEM_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_AddItemResponse>(&Handle_ADD_ITEM_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_ITEM_USE_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_ItemUseResponsePacket>(&Handle_ITEM_USE_RESPONSE, session, buffer, len);
        };

    // Add inventory packet handlers

    GPacketHandler[PKT_INVENTORY_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_InventoryResponsePacket>(&Handle_INVENTORY_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_MOVE_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_MoveResponsePacket>(&Handle_MOVE_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_MOVE_BROADCAST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_MoveBroadcastPacket>(&Handle_MOVE_BROADCAST, session, buffer, len);
        };

    GPacketHandler[PKT_ENTER_GAME_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
		      	//return instance.HandlePacket<Protocol::SC_EnterGameResponsePacket>(&Handle_ENTER_GAME_FROM_LOBBY_RESPONSE, session, buffer, len);
			      return instance.HandlePacket<Protocol::SC_EnterGameResponsePacket>(&Handle_ENTER_GAME_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_MONSTER_MOVE_REQUEST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket <Protocol::SC_MonsterMoveRequestPacket> (&Handle_MONSTER_MOVE_REQUEST, session, buffer, len);
        };
    GPacketHandler[PKT_MONTSER_MAPINFO_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket <Protocol::SC_MapMonsterInfoResponsePacket>(&Handle_MAP_INFO_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_MONSTER_ATTACK_REQUEST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SS_MonsterAttackRequestPacket>(&Handle_MONSTER_ATTACK_REQUEST, session, buffer, len);
        };
    GPacketHandler[PKT_ATTACK_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_AttackResponsePacket>(&Handle_ATTACK_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_GET_SKILL_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_GetSkillResponsePacket>(&Handle_GET_SKILL_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_CHANNEL_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_ChannelResponsePacket>(&Handle_CHANNEL_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_DAMAGE_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SS_DamageResponsePacket>(&Handle_DAMAGE_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_MONSTER_STATUS_BROADCAST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_MonsterStatusBroadcastPacket>(&Handle_MONSTER_STATUS_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_USER_QUEST_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_UserQuestInfoResponse>(&Handle_USER_QUEST_INFO_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_NPC_INFO_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_NPCInfoResponse>(&Handle_NPC_INFO_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_EQUIP_INFO_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_EquipInfoResponse>(&Handle_EQUIP_INFO_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_EQUIP_CHANGE_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_EquipChangeRespnse>(&Handle_EQUIP_CHANGE_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_MONSTER_DIE_REQUEST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::MonsterDieBroadcast>(&Handle_MONSTER_DIE_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_QUEST_ADD_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_QuestAddResponse>(&Handle_QUEST_ADD_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_QUEST_CHECK_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_QuestCheckResponse>(&Handle_QUEST_CHECK_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_QUEST_COMPLETE_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_QuestCompleteResponse>(&Handle_QUEST_COMPLETE_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_SHOP_BUY_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_BuyResponse>(&Handle_SHOP_BUY_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_SHOP_SELL_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_SellResponse>(&Handle_SHOP_SELL_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_USER_SPAWN_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_UserSpawnResponse>(&Handle_USER_SPAWN_RESPONSE, session, buffer, len);
        };

    GPacketHandler[PKT_DROP_REQUEST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_DropRequest>(&Handle_DROP_REQUEST, session, buffer, len);
        };
    GPacketHandler[PKT_EXP_INCREASE_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_ExpIncreaseResponse>(&Handle_EXP_INCREASE_REPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_PARTY_MAP_INFO_REQUEST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_PartyMapInfoRequest>(&Handle_PARTY_MAP_INFO_REQUEST, session, buffer, len);
        };
    GPacketHandler[PKT_PARTY_STATUS_UPDATE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_PartyStatusUpdate>(&Handle_PARTY_STATUS_UPDATE, session, buffer, len);
        };
    GPacketHandler[PKT_LEAVE_PARTY_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_LeavePartyResponse>(&Handle_LEAVE_PARTY_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_CREATE_PARTY_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_CreatePartyResponse>(&Handle_CREATE_PARTY_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_JOIN_PARTY_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_JoinPartyResponse>(&Handle_JOIN_PARTY_RESP0NSE, session, buffer, len);
        };
    GPacketHandler[PKT_ACTION_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
    {
        return instance.HandlePacket<Protocol::SC_ActionBroadcastPacket>(&Handle_ACTION_BROADCAST, session, buffer, len);
    };
    GPacketHandler[PKT_POST_SEND_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_PostSendResponse>(&Handle_POST_SEND_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_POST_GET_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_PostGetResponse>(&Handle_POST_GET_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_TRADE_USER_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_TradeUserResponse>(&Handle_TRADE_USER_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_TRADE_START_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_TradeStartResponse>(&Handle_TRADE_START_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_TRADE_STATE_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_TradeStateResponse>(&Handle_TRADE_STATE_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_TRADE_COMPLETE_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_TradeCompleteResponse>(&Handle_TRADE_COMPLETE_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_FRIEND_INFO_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_FriendInfoResponse>(&Handle_INFO_FRIEND_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_REQUEST_FRIEND_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_RequestFriendResponse>(&Handle_REQUEST_FRIEND_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_FRIEND_CONNECT_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_FriendConnectResponse>(&Handle_FRIEND_CONNECT_RESPONSE, session, buffer, len);
        };

    GPacketHandler[PKT_GOOD_USER_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_UserGoodResponse>(&Handle_USER_GOOD_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_GOOD_PLAYER_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_PlayerGoodResponse>(&Handle_PLAYER_GOOD_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_GUILD_INFO_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_GuildinfoResponse>(&Handle_INFO_GUILD_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_CREATE_GUILD_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_GuildCreateResponse>(&Handle_CREATE_GUILD_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_ACCEPT_GUILD_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_GuildAcceptResponse>(&Handle_ACCEPT_GUILD_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_REMOVE_GUILD_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_GuildRemoveResponse>(&Handle_REMOVE_GUILD_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_DELETE_GUILD_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_GuildDeleteResponse>(&Handle_DELETE_GUILD_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_INVITE_GUILD_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_GuildInviteResponse>(&Handle_INVITE_GUILD_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_CHANGE_NAME_GUILD_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_GuildChangeNameResponse>(&Handle_CHANGE_NAME_GUILD_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_CHANGE_RANK_GUILD_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_GuildChangeRankResponse>(&Handle_CHANGE_RANK_GUILD_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_GUILD_CONNECT_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_GuildConnectResponse>(&Handle_CONNECT_GUILD_RESPONSE, session, buffer, len);
        };
    
    GPacketHandler[PKT_COMMUNITY_LIST_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_CommunityListResponse>(&Handle_LIST_COMMUNITY_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_COMMUNITY_KICK_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_CommunityKickResponse>(&Handle_KICK_COMMUNITY_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_COMMUNITY_CONTENT_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_CommunityContentResponse>(&Handle_CONTENT_COMMUNITY_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_COMMUNITY_ACCEPT_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_CommunityAcceptResponse>(&Handle_ACCEPT_COMMUNITY_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_COMMUNITY_INVITE_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_CommunityInviteResponse>(&Handle_INVITE_COMMUNITY_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_OTHER_STATUS_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_OtherStatusResponse>(&Handle_OTHER_STATUS_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_CONTENT_ACCEPT_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_ContentAcceptResponse>(&Handle_ACCEPT_CONTENT_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_CONTENT_CANCEL_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_ContentCancelResponse>(&Handle_CANCEL_CONTENT_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_CONTENT_FAIL_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_ContentFailResponse>(&Handle_FAIL_CONTENT_RESPONSE, session, buffer, len);
        };

    GPacketHandler[PKT_MAP_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::SC_MapResponse>(&Handle_MAP_RESPONSE, session, buffer, len);
        };
}

bool ClientPacketHandler::HandlePacket(TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
{
    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

    return GPacketHandler[header->id](session, buffer, len);
}

PacketSession::PacketSession()
{
}

PacketSession::~PacketSession()
{
}

int32 PacketSession::OnRecv(BYTE* buffer, int32 len)
{
    int32 processLen = 0;

    while (true)
    {
        int32 dataSize = len - processLen;
        // �ּ��� ����� �Ľ��� �� �־�� �Ѵ�
        if (dataSize < sizeof(PacketHeader))
            break;

        PacketHeader header = *(reinterpret_cast<PacketHeader*>(&buffer[processLen]));
        // ����� ��ϵ� ��Ŷ ũ�⸦ �Ľ��� �� �־�� �Ѵ�
        if (dataSize < header.size)
            break;

        // ��Ŷ ���� ����
        OnRecvPacket(&buffer[processLen], header.size);

        processLen += header.size;
    }

    return processLen;
}
