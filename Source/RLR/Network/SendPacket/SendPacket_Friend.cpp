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
#include "Network/Proto/Friend.pb.h"

/*

    Friend.proto

*/

bool UNetworkManager::SendInfoFriend() {

    if (!MainServerSocket) return false;

    Protocol::CS_FriendInfoRequest packet;

    packet.set_userseq(UserSeq);

    SEND_PACKET(packet);
}

bool UNetworkManager::SendAddFriend(int friendSeq) {

    if (!MainServerSocket) return false;

    Protocol::CS_AddFriendRequest packet;

    packet.set_userseq(UserSeq);
    packet.set_friendseq(friendSeq);

    SEND_PACKET(packet);
}

bool UNetworkManager::SendRemoveFriend(int friendSeq)
{
    if (!MainServerSocket) return false;

    Protocol::CS_RemoveFriendRequest packet;

    packet.set_userseq(UserSeq);
    packet.set_friendseq(friendSeq);

    SEND_PACKET(packet);
}

bool UNetworkManager::SendCreateFriendGroup(string& groupName)
{
    if (!MainServerSocket) return false;

    Protocol::CS_CreateFriendGroupRequest packet;

    packet.set_userseq(UserSeq);
    packet.set_groupname(groupName);

    SEND_PACKET(packet);
}

bool UNetworkManager::SendRemoveFriendGroup(int groupSeq)
{
    if (!MainServerSocket) return false;

    Protocol::CS_RemoveFriendGroupRequest packet;

    packet.set_userseq(UserSeq);
    packet.set_groupseq(groupSeq);

    SEND_PACKET(packet);
}

bool UNetworkManager::SendMoveFriendInGroup(int friendSeq, int groupSeq)
{
    if (!MainServerSocket) return false;

    Protocol::CS_MoveFriendInGroupRequest packet;

    packet.set_userseq(UserSeq);
    packet.set_groupseq(groupSeq);
    packet.set_friendseq(friendSeq);

    SEND_PACKET(packet);
}

bool UNetworkManager::SendMoveFriendGroup(int groupSeq1, int groupSeq2)
{
    if (!MainServerSocket) return false;

    Protocol::CS_MoveFriendGroupRequest packet;

    packet.set_userseq(UserSeq);
    packet.set_groupseq1(groupSeq1);
    packet.set_groupseq2(groupSeq2);

    SEND_PACKET(packet);
    return false;
}
