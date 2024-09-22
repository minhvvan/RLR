// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/GameManager.h"

#include "Structs/ItemStructs.h"

#include "Network/LoadBalancerClient.h"
#include <Networking.h>
#include "Network/FNetworkReceiver.h"
#include <Network/Buffer.h>
#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Proto/Packet.pb.h"
#include "Network/Proto/Item.pb.h"
#include "Network/Proto/Trade.pb.h"


/*
	Trade 관련 패킷.
*/
bool UNetworkManager::SendTradeReqeust(int32 TargetUserSeq)
{
    if (!MainServerSocket) return false;

    /*
        거래 요청 보내기
    */

    int32 TradeUserSeq = GameInstance->GetPlayerManager()->GetUserSeq();

    Protocol::CS_TradeRequest packet;
    packet.set_userseq1(TradeUserSeq);
    packet.set_userseq2(TargetUserSeq);
    //SEND_PACKET(packet);
    return false;
}

bool UNetworkManager::SendAddTradeItem(const FItemData& NewTradeItem, int32 Quantity)
{
    if (!MainServerSocket) return false;

    /*
        개인거래창에 새로운 아이템 올리기
    */

    int32 TradeUserSeq = GameInstance->GetPlayerManager()->GetUserSeq();

    Protocol::CS_AddTradeItem packet;
    packet.set_userseq(TradeUserSeq);
    packet.set_quantity(Quantity);
    packet.set_itemid(NewTradeItem.ITEM_ID);
    //SEND_PACKET(packet);
    return false;
}

bool UNetworkManager::SendAddTradeCurrency(int32 Amount)
{
    if (!MainServerSocket) return false;

    /*
        개인거래창에 재화 올리기
    */

    int32 TradeUserSeq = GameInstance->GetPlayerManager()->GetUserSeq();

    Protocol::CS_AddTradeCurrency packet;
    packet.set_userseq(TradeUserSeq);
    packet.set_amount(Amount);
    //SEND_PACKET(packet);
    return false;
}

bool UNetworkManager::SendRemoveTradeItem(const FItemData& NewTradeItem, int32 Quantity)
{
    if (!MainServerSocket) return false;

    int32 TradeUserSeq = GameInstance->GetPlayerManager()->GetUserSeq();

    /*
    *   TODO
    *   현석님이 패킷 만들어주기
        개인거래창에 올린 아이템 제거
    */

    {
        //Protocol::CS_RemoveTradeItem packet;
        //packet.set_userseq(TradeUserSeq);
        //packet.set_itemid(NewTradeItem.ITEM_ID);
        //packet.set_quantity(Quantity);
        //SEND_PACKET(packet);
    }

    return false;
}

bool UNetworkManager::SendLockTrade()
{
    if (!MainServerSocket) return false;

    /*
        거래 잠금
    */

    int32 TradeUserSeq = GameInstance->GetPlayerManager()->GetUserSeq();

    Protocol::CS_LockTrade packet;
    packet.set_userseq(TradeUserSeq);
    //SEND_PACKET(packet);
    return false;
}

bool UNetworkManager::SendUnLockTrade()
{
    if (!MainServerSocket) return false;

    /*
        거래 잠금 해제
    */

    /*
    *   TODO
    *   현석님이 패킷 만들어주기
    */

    int32 TradeUserSeq = GameInstance->GetPlayerManager()->GetUserSeq();

	//Protocol::CS_UnLockTrade packet;
	//packet.set_userseq(TradeUserSeq);
    //SEND_PACKET(packet);
    return false;
}

bool UNetworkManager::SendConfirmTrade()
{
    if (!MainServerSocket) return false;

    /*
        거래 확인
    */

    /*
    *   TODO
    *   현석님이 패킷 만들어주기
    */

    int32 TradeUserSeq = GameInstance->GetPlayerManager()->GetUserSeq();

    {
        //Protocol::CS_ConfirmTrade packet;
        //packet.set_userseq(TradeUserSeq);
        //SEND_PACKET(packet);
    }
    return false;
}

bool UNetworkManager::SendCancelTrade()
{
    if (!MainServerSocket) return false;

    /*
        거래 취소
    */

    int32 TradeUserSeq = GameInstance->GetPlayerManager()->GetUserSeq();

    Protocol::CS_CancelTrade packet;
    packet.set_userseq(TradeUserSeq);
    //SEND_PACKET(packet);
    return false;
}