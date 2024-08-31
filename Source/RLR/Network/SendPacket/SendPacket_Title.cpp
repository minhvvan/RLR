// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/GameManager.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

#include "Network/LoadBalancerClient.h"
#include <Networking.h>
#include "Network/FNetworkReceiver.h"
#include <Network/Buffer.h>
#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Proto/Packet.pb.h"
#include "Network/Proto/Skill.pb.h"
#include "Network/Proto/Item.pb.h"

/*

    Title.proto

*/

bool UNetworkManager::SendServerListRequest()
{
    /*
        현석님이 잘 해주겠지.
    */

    DEBUG_INCOMPLETE;

    return false;
}

bool UNetworkManager::SendLoginRequest(int32 ServerSeq, FText ID, FText PW)
{
    /*
        현석님이 잘 해주겠지.
    */

    DEBUG_INCOMPLETE;

    return false;
}