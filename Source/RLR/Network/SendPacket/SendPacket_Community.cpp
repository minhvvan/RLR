// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/GameManager.h"
#include "Structs/ItemStructs.h"
#include "GameManager/LevelManager.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

#include "Network/LoadBalancerClient.h"
#include <Networking.h>
#include "Network/FNetworkReceiver.h"
#include <Network/Buffer.h>
#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Proto/Packet.pb.h"
#include "Network/Proto/Community.pb.h"

/*
	Community 관련 패킷.
*/
bool UNetworkManager::SendOtherStatus(int userSeq) {
	if (!MainServerSocket) return false;

	Protocol::CS_OtherStatusRequest packet;

	packet.set_userseq(userSeq);

	SEND_PACKET(packet);
}

bool UNetworkManager::SendListCommunity(int communityType)
{
	if (!MainServerSocket) return false;

	Protocol::CS_CommunityListRequest packet;

	packet.set_communitytype(communityType);

	SEND_PACKET(packet);
}

bool UNetworkManager::SendEnterCommunity(int communitySeq)
{
	if (!MainServerSocket) return false;

	Protocol::CS_CommunityEnterRequest packet;

	packet.set_communityseq(communitySeq);

	SEND_PACKET(packet);
}

bool UNetworkManager::SendAcceptCommunity(int userSeq, int communitySeq)
{
	if (!MainServerSocket) return false;

	Protocol::CS_CommunityAcceptRequest packet;

	packet.set_userseq(userSeq);
	packet.set_communityseq(communitySeq);

	SEND_PACKET(packet);
}

bool UNetworkManager::SendInviteCommunity(FText userName,int communitySeq)
{
	if (!MainServerSocket) return false;

	Protocol::CS_CommunityInviteRequest packet;
	FString userFString = userName.ToString();

	// FString을 std::string으로 변환
	std::string userStdString(TCHAR_TO_UTF8(*userFString));
	packet.set_username(userStdString);
	packet.set_communityseq(communitySeq);

	SEND_PACKET(packet);
}

bool UNetworkManager::SendExitCommunity(int communitySeq)
{
	if (!MainServerSocket) return false;

	Protocol::CS_CommunityExitRequest packet;

	packet.set_userseq(UserSeq);
	packet.set_communityseq(communitySeq);

	SEND_PACKET(packet);
}

bool UNetworkManager::SendCreateCommunity(FText title, int communityType)
{
	if (!MainServerSocket) return false;

	Protocol::CS_CommunityCreateRequest packet;
	FString titleFString = title.ToString();

	// FString을 std::string으로 변환
	std::string titleStdString(TCHAR_TO_UTF8(*titleFString));
	packet.set_userseq(UserSeq);
	packet.set_title(titleStdString);
	packet.set_communitytype(communityType);

	SEND_PACKET(packet);
}

bool UNetworkManager::SendKickCommunity(int userSeq, int communitySeq)
{
	if (!MainServerSocket) return false;

	Protocol::CS_CommunityKickRequest packet;

	packet.set_userseq(userSeq);
	packet.set_communityseq(communitySeq);

	SEND_PACKET(packet);
}

bool UNetworkManager::SendContentCommunity(int communityKey, int communitySeq)
{
	if (!MainServerSocket) return false;

	Protocol::CS_CommunityContentRequest packet;

	packet.set_communitykey(communityKey);
	packet.set_communityseq(communitySeq);

	SEND_PACKET(packet);
}
bool UNetworkManager::SendCancelContent(int communitySeq)
{
	if (!MainServerSocket) return false;

	Protocol::CS_ContentCancelRequest packet;

	packet.set_userseq(UserSeq);
	packet.set_communityseq(communitySeq);

	SEND_PACKET(packet);
}

bool UNetworkManager::SendAcceptContent(int communitySeq)
{
	if (!MainServerSocket) return false;

	Protocol::CS_ContentAcceptRequest packet;

	packet.set_userseq(UserSeq);
	packet.set_communityseq(communitySeq);

	SEND_PACKET(packet);
}
