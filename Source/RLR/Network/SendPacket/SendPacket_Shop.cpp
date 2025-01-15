// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "Network/LoadBalancerClient.h"
#include <Networking.h>
#include "Network/FNetworkReceiver.h"
#include <Network/Buffer.h>
#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Proto/Packet.pb.h"
#include "Network/Proto/Skill.pb.h"
#include "Network/Proto/Item.pb.h"
#include "Network/Proto/Shop.pb.h"

/*

    상점 관련 패킷

*/


bool UNetworkManager::SendBuyPacket(int itemSeq, int shopSeq, int quantity) {
    if (!MainServerSocket) return false;

    Protocol::CS_BuyRequest packet;

    packet.set_userseq(GameInstance->GetUserSeq());
    packet.set_itemseq(itemSeq);
    packet.set_shopseq(shopSeq);
    packet.set_quantity(quantity);
    

    SEND_PACKET(packet);
}

bool UNetworkManager::SendSellPacket(int64 itemId, int shopSeq, int quantity) {
    if (!MainServerSocket) return false;

    Protocol::CS_SellRequest packet;
    UE_LOG(LogTemp, Log, TEXT("Sell Packet Request Start!!"));
    packet.set_userseq(GameInstance->GetUserSeq());
    packet.set_itemid(itemId);
    packet.set_shopseq(shopSeq);
    packet.set_quantity(quantity);


    SEND_PACKET(packet);
}