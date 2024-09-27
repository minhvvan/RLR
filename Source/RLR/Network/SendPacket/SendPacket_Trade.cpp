// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/LevelManager.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

#include "Network/LoadBalancerClient.h"
#include <Networking.h>
#include "Network/FNetworkReceiver.h"
#include <Network/Buffer.h>
#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Proto/Packet.pb.h"
#include "Network/Proto/Skill.pb.h"
#include "Network/Proto/Trade.pb.h"

/*

    Trade.proto

*/

bool UNetworkManager::SendTradeStartRequest(int userSeq2) {

    if (!MainServerSocket) return false;

    Protocol::CS_TradeStartRequest packet;
    packet.set_userseq1(UserSeq);
    packet.set_userseq2(userSeq2);
    
    SEND_PACKET(packet);
}
bool UNetworkManager::SendTradeUserRequest(int userSeq2) {

    if (!MainServerSocket) return false;

    Protocol::CS_TradeUserRequest packet;
    packet.set_userseq1(UserSeq);
    packet.set_userseq2(userSeq2);

    SEND_PACKET(packet);
}
bool UNetworkManager::SendTradeLockRequest() {

    if (!MainServerSocket) return false;

    Protocol::CS_TradeLockRequest packet;
    packet.set_userseq(UserSeq);


    SEND_PACKET(packet);
}
bool UNetworkManager::SendTradeCancelRequest() {

    if (!MainServerSocket) return false;

    Protocol::CS_TradeCancelRequest packet;
    packet.set_userseq(UserSeq);


    SEND_PACKET(packet);
}
bool UNetworkManager::SendTradeAddItemRequest(int64 itemId, int64 itemValue) {

    if (!MainServerSocket) return false;

    Protocol::CS_TradeAddItemRequest packet;
    packet.set_userseq(UserSeq);
    packet.set_itemid(itemId);
    packet.set_itemvalue(itemValue);


    SEND_PACKET(packet);
}
bool UNetworkManager::SendTradeAddGoodRequest(int64 totalMoney) {

    if (!MainServerSocket) return false;

    Protocol::CS_TradeAddGoodRequest packet;
    packet.set_userseq(UserSeq);
    packet.set_totalmoney(totalMoney);

    SEND_PACKET(packet);
}