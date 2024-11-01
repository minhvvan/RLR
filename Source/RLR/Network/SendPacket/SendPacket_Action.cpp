// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "Network/Proto/Action.pb.h"
#include "Network/Handler/ClientPacketHandler.h"
#include "ActionSystem/ActionSystemComponent.h"


bool UNetworkManager::SendActionPacket(int32 userSeq, string tagName)
{
    Protocol::CS_ActionRequestPacket packet;
    packet.set_userseq(userSeq);
    packet.set_tagname(tagName);

    SEND_PACKET(packet);
   
    return false;
}