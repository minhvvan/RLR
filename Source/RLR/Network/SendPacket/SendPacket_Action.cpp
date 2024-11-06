// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "Network/Proto/Action.pb.h"
#include "Network/Handler/ClientPacketHandler.h"
#include "ActionSystem/ActionSystemComponent.h"


bool UNetworkManager::SendActionPacket(FActionResult actionResult)
{
    Protocol::CS_ActionRequestPacket packet;
    packet.set_userseq(actionResult.UserSeq);
    packet.set_actionseq(actionResult.ActionSeq);
    packet.set_channelid(actionResult.ChannelId);
    packet.set_transx(actionResult.TargetTransform.X);
    packet.set_transy(actionResult.TargetTransform.Y);
    packet.set_transz(actionResult.TargetTransform.Z);
    
    SEND_PACKET(packet);
   
    return false; 
}