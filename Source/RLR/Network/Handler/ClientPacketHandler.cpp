#include "ClientPacketHandler.h"
#include "GameManager/GameManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/MonsterManager.h"
#include "Network/Buffer.h"
//UI
#include "UI/MainUI.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/CharacterStatus/CharacterStatusUI.h"
#include "UI/InGame/CharacterStatus/Equipment/EquipmentUI.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "CertificationPacketHandler.h"
#include "InfoPacketHandler.h"
#include "ItemPacketHandler.h"
#include "CommunityPacketHandler.h"
#include "ActionPacketHandler.h"

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

    GPacketHandler[PKT_LOGIN_REQUEST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::LoginRequestPacket>(&Handle_LOGIN_REQUEST, session, buffer, len);
        };
    GPacketHandler[PKT_LOGIN_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::LoginResponsePacket>(&Handle_LOGIN_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_CHARACTER_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::CharacterResponsePacket>(&Handle_CHARACTER_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_STATUS_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::StatusResponsePacket>(&Handle_STATUS_RESPONSE, session, buffer, len);
        };
    // Add item packet handlers
    GPacketHandler[PKT_ITEM_ADD_REQUEST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::ItemAddRequestPacket>(&Handle_ITEM_ADD_REQUEST, session, buffer, len);
        };
    GPacketHandler[PKT_ITEM_USE_REQUEST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::ItemUseRequestPacket>(&Handle_ITEM_USE_REQUEST, session, buffer, len);
        };

    // Add inventory packet handlers

    GPacketHandler[PKT_INVENTORY_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::InventoryResponsePacket>(&Handle_INVENTORY_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_MOVE_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::MoveResponsePacket>(&Handle_MOVE_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_MOVE_BROADCAST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::MoveBroadcastPacket>(&Handle_MOVE_BROADCAST, session, buffer, len);
        };
    GPacketHandler[PKT_ENTER_GAME_REQUEST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::EnterGamePacket>(&Handle_ENTER_GAME_REQUEST, session, buffer, len);
        };

    GPacketHandler[PKT_ENTER_GAME_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::EnterGameResponsePacket>(&Handle_ENTER_GAME_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_MONSTER_MOVE_REQUEST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket <Protocol::MonsterMoveRequestPacket> (&Handle_MONSTER_MOVE_REQUEST, session, buffer, len);
        };
    GPacketHandler[PKT_MONTSER_MAPINFO_REQUEST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket <Protocol::MapMonsterInfoRequestPacket>(&Handle_MAP_INFO_REQUEST, session, buffer, len);
        };
    GPacketHandler[PKT_MONTSER_MAPINFO_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket <Protocol::MapMonsterInfoResponsePacket>(&Handle_MAP_INFO_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_MONSTER_ATTACK_REQUEST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::MonsterAttackRequestPacket>(&Handle_MONSTER_ATTACK_REQUEST, session, buffer, len);
        };
    GPacketHandler[PKT_ATTACK_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::AttackResponsePacket>(&Handle_ATTACK_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_GET_SKILL_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::GetSkillResponsePacket>(&Handle_GET_SKILL_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_CHANNEL_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::ChannelResponsePacket>(&Handle_CHANNEL_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_DAMAGE_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::DamageResponsePacket>(&Handle_DAMAGE_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_MONSTER_STATUS_BROADCAST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::MonsterStatusBroadcastPacket>(&Handle_MONSTER_STATUS_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_USER_QUEST_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::UserQuestInfoResponse>(&Handle_USER_QUEST_INFO_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_NPC_INFO_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::NPCInfoResponse>(&Handle_NPC_INFO_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_EQUIP_INFO_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::EquipInfoResponse>(&Handle_EQUIP_INFO_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_EQUIP_CHANGE_RESPONSE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::EquipChangeRespnse>(&Handle_EQUIP_CHANGE_RESPONSE, session, buffer, len);
        };
    GPacketHandler[PKT_MONSTER_DIE_REQUEST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::MonsterDieBroadcast>(&Handle_MONSTER_DIE_RESPONSE, session, buffer, len);
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

// [size(2)][id(2)][data....][size(2)][id(2)][data....]
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
