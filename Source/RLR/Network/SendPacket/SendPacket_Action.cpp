// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "Network/Proto/Action.pb.h"
#include "Network/Handler/ClientPacketHandler.h"
#include "ActionSystem/ActionSystemComponent.h"


bool UNetworkManager::SendActionPacket(int32 userSeq, int actionSeq)
{
    Protocol::CS_ActionRequestPacket packet;
    packet.set_userseq(userSeq);
    packet.set_actionseq(actionSeq);

    SEND_PACKET(packet);
   
    return false; 
}