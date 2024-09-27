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
    packetPost->set_title(post.title);
    packetPost->set_postid(post.postId);
    packetPost->set_senderseq(UserSeq);
    packetPost->set_reseiverseq(post.reseiverSeq);
    packetPost->set_totalmoney(post.totalMoney);
    packetPost->set_content(post.content);
    SEND_PACKET(packet);
}


bool UNetworkManager::SendPostReadRequest(FPostResult post) {

    if (!MainServerSocket) return false;

    Protocol::CS_PostRead packet;
    packet.set_postid(post.postId);
    packet.set_userseq(UserSeq);

    SEND_PACKET(packet);
}
bool UNetworkManager::SendPostReceivedRequest(FPostResult post) {

    if (!MainServerSocket) return false;

    Protocol::CS_PostReceived packet;
    packet.set_postid(post.postId);
    packet.set_userseq(UserSeq);

    SEND_PACKET(packet);
}