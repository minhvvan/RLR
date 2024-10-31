// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/GameManager.h"
#include "Structs/ItemStructs.h"
#include "GameManager/LevelManager.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

#include "Network/LoadBalancerClient.h"
#include <Networking.h>
#include "Network/FNetworkReceiver.h"
#include <Network/Buffer.h>
#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Proto/Packet.pb.h"
#include "Network/Proto/Item.pb.h"
#include "Network/Proto/Trade.pb.h"
#include "Network/Proto/Skill.pb.h"

/*
    Trade 관련 패킷.
*/

bool UNetworkManager::SendTradeUserRequest(int32 TargetUserSeq)
{
    if (!MainServerSocket) return false;

    /*
        거래 요청 보내기
    */

    int32 MySeq = GameInstance->GetPlayerManager()->GetUserSeq();

    Protocol::CS_TradeUserRequest packet;
    packet.set_userseq1(MySeq);
    packet.set_userseq2(TargetUserSeq);
    SEND_PACKET(packet);
    return false;
}

bool UNetworkManager::SendTradeStartReqeust(int32 TargetUserSeq)
{
    if (!MainServerSocket) return false;

    /*
        거래 요청 수락하기
    */

    int32 MySeq = GameInstance->GetPlayerManager()->GetUserSeq();

    Protocol::CS_TradeStartRequest packet;
    packet.set_userseq1(MySeq);
    packet.set_userseq2(TargetUserSeq);
    SEND_PACKET(packet);
    return false;
}

bool UNetworkManager::SendTradeAddItemReqeust(const FItemData& NewTradeItem, int32 Quantity)
{
    if (!MainServerSocket) return false;

    /*
        개인거래창에 새로운 아이템 올리기
    */

    int32 MySeq = GameInstance->GetPlayerManager()->GetUserSeq();

    Protocol::CS_TradeAddItemRequest packet;
    packet.set_userseq(MySeq);
    packet.set_itemvalue(Quantity);
    packet.set_itemid(NewTradeItem.ITEM_ID);
    SEND_PACKET(packet);
    return false;
}

bool UNetworkManager::SendTradeAddGoodReqeust(int32 Amount)
{
    if (!MainServerSocket) return false;

    /*
        개인거래창에 재화 올리기
    */

    int32 MySeq = GameInstance->GetPlayerManager()->GetUserSeq();

    Protocol::CS_TradeAddGoodRequest packet;
    packet.set_userseq(MySeq);
    packet.set_totalmoney(Amount);
    SEND_PACKET(packet);
    return false;
}

bool UNetworkManager::SendTradeLockRequest()
{
    if (!MainServerSocket) return false;

    /*
        거래 잠금
    */

    int32 MySeq = GameInstance->GetPlayerManager()->GetUserSeq();

    Protocol::CS_TradeLockRequest packet;
    packet.set_userseq(MySeq);
    SEND_PACKET(packet);
    return false;
}

bool UNetworkManager::SendTradeCancelReqeust()
{
    if (!MainServerSocket) return false;

    /*
        거래 취소
    */

    int32 MySeq = GameInstance->GetPlayerManager()->GetUserSeq();
    Protocol::CS_TradeCancelRequest packet;
    packet.set_userseq(MySeq);
    SEND_PACKET(packet);
    return false;
}