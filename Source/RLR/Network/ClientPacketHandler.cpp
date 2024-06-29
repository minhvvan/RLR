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
bool Handle_C_ITEM_ADD(TSharedPtr<PacketSession>& session, Protocol::C_ITEM_ADD& pkt)
{
    // Handle item add
    
    UInventoryManager* InventoryManager = GameInstance->GetInventoryManager();
    FItemData itemData;

    itemData.MakeItemData(pkt.item());
    InventoryManager->AddItem(itemData);
    return true;
}

bool Handle_C_ITEM_USE(TSharedPtr<PacketSession>& session, Protocol::C_ITEM_USE& pkt)
{
    // Handle item use
    return true;
}

// Inventory Handlers
bool Handle_INVENTORY_REQUEST(TSharedPtr<PacketSession>& session, Protocol::InventoryRequestPacket& pkt)
{
    // Handle inventory request

    Protocol::InventoryRequestPacket response;
    response.set_userseq(pkt.userseq());
   
   

    return true;
}

bool Handle_INVENTORY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::InventoryResponsePacket& pkt)
{
    UInventoryManager* InventoryManager = GameInstance->GetInventoryManager();
    TArray<FItemData> itemDatas;
    for (int32 i = 0; i < pkt.items_size(); i++) {
        FItemData itemData;
        itemData.MakeItemData(pkt.items().at(i));
        itemDatas.Add(itemData);
    }
   
    InventoryManager->GetItemList(itemDatas);
  
    
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

    // Add item packet handlers
    GPacketHandler[PKT_C_ITEM_ADD] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::C_ITEM_ADD>(&Handle_C_ITEM_ADD, session, buffer, len);
        };
    GPacketHandler[PKT_C_ITEM_USE] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::C_ITEM_USE>(&Handle_C_ITEM_USE, session, buffer, len);
        };

    // Add inventory packet handlers
    GPacketHandler[PKT_INVENTORY_REQUEST] = [](TSharedPtr<PacketSession>& session, uint8* buffer, int32 len)
        {
            return instance.HandlePacket<Protocol::InventoryRequestPacket>(&Handle_INVENTORY_REQUEST, session, buffer, len);
        };
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
