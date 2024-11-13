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
#include "Network/Proto/Post.pb.h"
#include "Structs/UtilStructs.h"
/*

    Post.proto

*/

bool UNetworkManager::SendPostRequest(FPostResult post) {

    if (!MainServerSocket) return false;

    Protocol::CS_PostRequest packet;

    auto* packetPost = packet.mutable_posts();
    std::string title(TCHAR_TO_UTF8(*post.Title));
    std::string content(TCHAR_TO_UTF8(*post.Content));
    std::string receiverName(TCHAR_TO_UTF8(*post.ReceiverName));
    packetPost->set_title(title);
    
    for (int64 Item : post.ItemId) {
        packetPost->add_itemid(Item);
    }
    
    for (const auto& ItemValue : post.ItemValues) {
        (*packetPost->mutable_itemvalues())[ItemValue.Key] = ItemValue.Value;
    }

    packetPost->set_postid(post.PostId);
    packetPost->set_senderseq(GameInstance->GetUserSeq());
    packetPost->set_receiverseq(post.ReceiverSeq);
    packetPost->set_receivername(receiverName);
    packetPost->set_totalmoney(post.TotalMoney);
    packetPost->set_content(content);
    SEND_PACKET(packet);
}
bool UNetworkManager::SendPostGetRequest() {

    if (!MainServerSocket) return false;

    Protocol::CS_PostGetRequest packet;

  
    packet.set_userseq(GameInstance->GetUserSeq());
    SEND_PACKET(packet);
}
bool UNetworkManager::SendPostRemoveRequest(FPostResult post) {

    if (!MainServerSocket) return false;

    Protocol::CS_RemovePostRequest packet;
    packet.set_postid(post.PostId);
    packet.set_userseq(GameInstance->GetUserSeq());

    SEND_PACKET(packet);
}

bool UNetworkManager::SendPostReadRequest(FPostResult post) {

    if (!MainServerSocket) return false;

    Protocol::CS_PostRead packet;
    packet.set_postid(post.PostId);
    packet.set_userseq(GameInstance->GetUserSeq());

    SEND_PACKET(packet);
}
bool UNetworkManager::SendPostReceivedRequest(FPostResult post) {

    if (!MainServerSocket) return false;

    Protocol::CS_PostReceived packet;
    packet.set_postid(post.PostId);
    packet.set_userseq(GameInstance->GetUserSeq());

    SEND_PACKET(packet);
}