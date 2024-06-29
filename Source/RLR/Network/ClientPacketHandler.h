#pragma once

#include "CoreMinimal.h"
#include "Packet.pb.h"
#include <functional>
#include <memory>
#include "Buffer.h"
class PacketSession;
struct PacketHeader;

using PacketHandlerFunc = bool(*)(TSharedPtr<PacketSession>&, uint8*, int32);
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum : uint16
{
    // Add Login Packet types
    PKT_LOGIN_REQUEST = 1001,
    PKT_LOGIN_RESPONSE = 1002,
    // Add item packet types
    PKT_C_ITEM_ADD = 1006,
    PKT_S_ITEM_ADD = 1007,
    PKT_C_ITEM_USE = 1008,
    PKT_S_ITEM_USE = 1009,
    // Add inventory packet types
    PKT_INVENTORY_REQUEST = 1010,
    PKT_INVENTORY_RESPONSE = 1011,
};

// Custom Handlers
bool Handle_INVALID(TSharedPtr<PacketSession>& session, uint8* buffer, int32 len);
// Login Handlers
bool Handle_LOGIN_REQUEST(TSharedPtr<PacketSession>& session, Protocol::LoginRequestPacket& pkt);
bool Handle_LOGIN_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::LoginResponsePacket& pkt);
// Item Handlers
bool Handle_C_ITEM_ADD(TSharedPtr<PacketSession>& session, Protocol::C_ITEM_ADD& pkt);
bool Handle_C_ITEM_USE(TSharedPtr<PacketSession>& session, Protocol::C_ITEM_USE& pkt);
// Inventory Handlers
bool Handle_INVENTORY_REQUEST(TSharedPtr<PacketSession>& session, Protocol::InventoryRequestPacket& pkt);
bool Handle_INVENTORY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::InventoryResponsePacket& pkt);

class ClientPacketHandler
{
public:
    static void Init();

    bool HandlePacket(TSharedPtr<PacketSession>& session, uint8* buffer, int32 len);

    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::LoginRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_LOGIN_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::LoginResponsePacket& pkt) { return MakeSendBuffer(pkt, PKT_LOGIN_RESPONSE); }
    // Add item make send buffer
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::S_ITEM_ADD& pkt) { return MakeSendBuffer(pkt, PKT_S_ITEM_ADD); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::S_ITEM_USE& pkt) { return MakeSendBuffer(pkt, PKT_S_ITEM_USE); }
    // Add inventory make send buffer
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::InventoryResponsePacket& pkt) { return MakeSendBuffer(pkt, PKT_INVENTORY_RESPONSE); }

private:
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

struct PacketHeader
{
    uint16 size;
    uint16 id; // ��������ID (ex. 1=�α���, 2=�̵���û)
};

class PacketSession 
{
public:
    PacketSession();
    virtual ~PacketSession();


protected:
    virtual int32		OnRecv(BYTE* buffer, int32 len) sealed;
    virtual void		OnRecvPacket(BYTE* buffer, int32 len) abstract;
};