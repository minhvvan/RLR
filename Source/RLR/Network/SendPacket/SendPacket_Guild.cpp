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
#include "Network/Proto/Guild.pb.h"

/*
	Guild 관련 패킷.
*/
bool UNetworkManager::SendInfoGuild() {
	if (!MainServerSocket) return false;

	Protocol::CS_GuildInfoRequest packet;

	packet.set_userseq(GameInstance->GetUserSeq());
	

	SEND_PACKET(packet);
}
bool UNetworkManager::SendAddGuild(int userSeq, int guildSeq) {
	if (!MainServerSocket) return false;

	Protocol::CS_GuildAddRequest packet;

	packet.set_guildseq(guildSeq);
	packet.set_userseq(userSeq);

	SEND_PACKET(packet);
}

bool UNetworkManager::SendRemoveGuild(int userSeq, int guildSeq) {
	if (!MainServerSocket) return false;

	Protocol::CS_GuildRemoveRequest packet;

	packet.set_guildseq(guildSeq);
	packet.set_userseq(userSeq);

	SEND_PACKET(packet);
}

bool UNetworkManager::SendInviteGuild(int userSeq, int guildSeq)
{
	if (!MainServerSocket) return false;

	Protocol::CS_GuildInviteRequest packet;

	packet.set_guildseq(guildSeq);
	packet.set_otherseq(userSeq);

	SEND_PACKET(packet);
	return false;
}

bool UNetworkManager::SendAcceptGuild(int guildSeq)
{
	if (!MainServerSocket) return false;

	Protocol::CS_GuildAcceptRequest packet;

	packet.set_guildseq(guildSeq);
	packet.set_otherseq(GameInstance->GetUserSeq());

	SEND_PACKET(packet);
	return false;
}

bool UNetworkManager::SendCreateGuild()
{
	if (!MainServerSocket) return false;

	Protocol::CS_GuildCreateRequest packet;

	packet.set_userseq(GameInstance->GetUserSeq());

	SEND_PACKET(packet);
	return false;
}

bool UNetworkManager::SendDeleteGuild(int guildSeq)
{
	if (!MainServerSocket) return false;

	Protocol::CS_GuildDeleteRequest packet;

	packet.set_guildseq(guildSeq);

	SEND_PACKET(packet);
	return false;
}

bool UNetworkManager::SendChangeNameGuild(int guildSeq, FText guildName)
{
	if (!MainServerSocket) return false;
	FString guildFString = guildName.ToString();

	// FString을 std::string으로 변환
	std::string guildStdString(TCHAR_TO_UTF8(*guildFString));
	Protocol::CS_GuildChangeNameRequest packet;

	packet.set_guildseq(guildSeq);
	packet.set_guildname(guildStdString);

	SEND_PACKET(packet);
	return false;
}

bool UNetworkManager::SendChangeRankGuild(int userSeq, int guildSeq, int guildRank)
{
	if (!MainServerSocket) return false;

	Protocol::CS_GuildChangeRankRequest packet;

	packet.set_guildseq(guildSeq);
	packet.set_userseq(userSeq);
	packet.set_guildrankseq(guildRank);
	SEND_PACKET(packet);
	return false;
}
