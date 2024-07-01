#include "ClientPacketHandler.h"
#include "../GameManager/GameManager.h"
#include "../GameManager/InventoryManager.h"
#include "Buffer.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
{
    // Handle invalid packet
    return false;
}

// Login Handlers
bool Handle_LOGIN_REQUEST(TSharedPtr<PacketSession>& session, Protocol::LoginRequestPacket& pkt)
{
    // Handle login request
    return true;
}

bool Handle_LOGIN_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::LoginResponsePacket& pkt)
{
    // Handle login response
    return true;
}

// Item Handlers
bool Handle_ITEM_ADD_REQUEST(TSharedPtr<PacketSession>& session, Protocol::ItemAddRequestPacket& pkt)
{
    FItemData itemData;

    itemData.MakeItemData(pkt.item());
    GameInstance->GetInventoryManager()->AddItem(itemData);
    return true;
}

bool Handle_STATUS_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::StatusResponsePacket& pkt) {
    
    pkt.usercharacter().setstatus().userhp();
    return true;
}
bool Handle_ITEM_USE_REQUEST(TSharedPtr<PacketSession>& session, Protocol::ItemUseRequestPacket& pkt)
{
    // Handle item use
    return true;
}


bool Handle_INVENTORY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::InventoryResponsePacket& pkt)
{
    
    TArray<FItemData> itemDatas;
    for (int32 i = 0; i < pkt.items_size(); i++) {
        FItemData itemData;
        itemData.MakeItemData(pkt.items().at(i));

        itemDatas.Add(itemData);
    }
   
    GameInstance->GetInventoryManager()->GetItemList(itemDatas);
  
    
    return true;
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
