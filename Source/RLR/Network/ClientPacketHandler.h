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
    // Add Status Packet types
    PKT_STATUS_REQUEST = 1003,
    PKT_STATUS_RESPONSE = 1004,
    // Add item packet types
    PKT_ITEM_ADD_REQUEST = 1006,
    PKT_ITEM_ADD_RESPONSE = 1007,
    PKT_ITEM_USE_REQUEST = 1008,
    PKT_ITEM_USE_RESPONSE = 1009,
    // Add inventory packet types
    PKT_INVENTORY_REQUEST = 1010,
    PKT_INVENTORY_RESPONSE = 1011,
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

class ClientPacketHandler
{
public:
    static void Init();

    bool HandlePacket(TSharedPtr<PacketSession>& session, uint8* buffer, int32 len);

    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::LoginRequestPacket& pkt) { return MakeSendBuffer(pkt, PKT_LOGIN_REQUEST); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::LoginResponsePacket& pkt) { return MakeSendBuffer(pkt, PKT_LOGIN_RESPONSE); }
    // Add item make send buffer
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::ItemAddResponsePacket& pkt) { return MakeSendBuffer(pkt, PKT_ITEM_ADD_RESPONSE); }
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::ItemUseResponsePacket& pkt) { return MakeSendBuffer(pkt, PKT_ITEM_USE_RESPONSE); }
    // Add inventory make send buffer
    static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::InventoryResponsePacket& pkt) { return MakeSendBuffer(pkt, PKT_INVENTORY_RESPONSE); }

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

struct PacketHeader
{
    uint16 size;
    uint16 id; // ��������ID (ex. 1=�α���, 2=�̵���û)
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