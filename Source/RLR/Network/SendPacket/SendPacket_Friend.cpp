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

    Friend.proto

*/

bool UNetworkManager::SendAddFriend(int userSeq) {

    return false;
}

bool UNetworkManager::SendRemoveFriend(int userSeq)
{
    return false;
}

bool UNetworkManager::SendCreateFriendGroup(string& groupName)
{
    return false;
}

bool UNetworkManager::SendRemoveFriendGroup(int groupSeq)
{
    return false;
}

bool UNetworkManager::SendMoveFriendInGroup(int friendSeq, int groupSeq)
{
    return false;
}

bool UNetworkManager::SendMoveFriendGroup(int groupSeq1, int groupSeq2)
{
    return false;
}
