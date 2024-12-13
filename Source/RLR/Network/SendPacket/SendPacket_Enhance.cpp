// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Proto/Enhance.pb.h"

bool UNetworkManager::SendEnhancePacket(int itemId, int userSeq, int addItemSeq, int addItemQuantity)
{
	if (!MainServerSocket) return false;

	Protocol::CS_EnhanceRequest packet;

	packet.set_itemid(itemId);
	packet.set_userseq(userSeq);
	packet.set_additemseq(addItemSeq);
	packet.set_additemquantity(addItemQuantity);

	SEND_PACKET(packet);
}