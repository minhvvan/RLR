#include "ClientPacketHandler.h"
#include "../GameManager/GameManager.h"
#include "../GameManager/InventoryManager.h"
#include "../GameManager/NetworkManager.h"
#include "../GameManager/MonsterManager.h"
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
    FString serverAddress = UTF8_TO_TCHAR(pkt.gameserveraddress().c_str());
    GameInstance->GetNetworkManager()->ConnectToLobbyServer(serverAddress, pkt.gameserverport());
    return true;
}
bool Handle_CHARACTER_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::CharacterResponsePacket& pkt) {

    Protocol::EnterGamePacket packet;
    packet.set_userseq(1);
   
    TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
    GameInstance->GetNetworkManager()->SendToLobbySocket(sendBuffer);

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
    
    UE_LOG(LogTemp, Log, TEXT("User level : %d"), pkt.usercharacter().level());
    UE_LOG(LogTemp, Log, TEXT("User hp : %d"), pkt.usercharacter().setstatus().userhp());
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
bool Handle_MOVE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::MoveResponsePacket& pkt) {
    return true;
}
bool Handle_MOVE_BROADCAST(TSharedPtr<PacketSession>& session, Protocol::MoveBroadcastPacket& pkt) {
    // TODO : OTHERUSERMAGER 연결하여 다른 유저의 위치 연동
    UE_LOG(LogTemp, Log, TEXT("User seq : %d"), pkt.userseq());
    UE_LOG(LogTemp, Log, TEXT("User Trans X : %d"), pkt.transx());
    UE_LOG(LogTemp, Log, TEXT("User Trans Y : %d"), pkt.transy());
    UE_LOG(LogTemp, Log, TEXT("User Trans Z : %d"), pkt.transz());
    return true;
}
bool Handle_MONSTER_ATTACK_REQUEST(TSharedPtr<PacketSession>& session, Protocol::MonsterAttackRequestPacket& pkt) {

    return false;
}
bool Handle_MONSTER_MOVE_REQUEST(TSharedPtr<PacketSession>& session, Protocol::MonsterMoveRequestPacket& pkt)
{
    // TODO :  몬스터 아이디를 통해 몬스터 매니저에있는 monster Data 중 Search하여 해당 몬스터의 좌표 변경 + 애니메이션 

      GameInstance->GetMonsterManager()->UpdateMonsterToMonsterId(pkt.monsterid(),pkt.transx(), pkt.transy(), pkt.transz());

    return false;
}
bool Handle_ATTACK_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::AttackResponsePacket& pkt) {

    return false;
}
bool Handle_MAP_INFO_REQUEST(TSharedPtr<PacketSession>& session, Protocol::MapMonsterInfoRequestPacket& pkt) {


    return false;
}
bool Handle_MAP_INFO_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::MapMonsterInfoResponsePacket& pkt) {
   
    TArray< FMonsterStatus> monsterDatas;
    for (int i = 0; i < pkt.monsters_size(); i++) {
        FMonsterStatus monsterData;
        monsterData.MakeMonsterData(pkt.monsters().at(i));
        monsterDatas.Add(monsterData);
    
    }

    GameInstance->GetMonsterManager()->SetMonsterData(monsterDatas);

    

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
}
bool Handle_ENTER_GAME_REQUEST(TSharedPtr<PacketSession>& session, Protocol::EnterGamePacket& pkt)
{
    return false;
}
bool Handle_ENTER_GAME_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::EnterGameResponsePacket& pkt)
{
    if (pkt.success())
    {
        FString MainServerAddress = UTF8_TO_TCHAR(pkt.mainserveraddress().c_str());
        FString MonsterServerAddress = UTF8_TO_TCHAR(pkt.monsterserveraddress().c_str());
        GameInstance->GetNetworkManager()->ConnectToMainServer(MainServerAddress, pkt.mainserverport());
        GameInstance->GetNetworkManager()->ConnectToMonsterServer(MonsterServerAddress, pkt.monsterserverport());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to enter game"));
    }

    return true;
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
