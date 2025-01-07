// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/GuildPacketHandler.h"
#include "GameManager/GuildManager.h"
#include "GameManager/GameManager.h"
#include "Structs/UtilStructs.h"

/*
	GuildQeustInfoResponse가 추가된다면
	FGuildQuest questData;
	questData.MakeQuestData(pkt.quests());

	GameInstance->GetGuildManager()->SetGuildQuestData(questData);
*/
bool Handle_INFO_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildinfoResponse& pkt)
{
	FGuildResult Guild;
	Guild.MakeGuildData(pkt.guild());

	GameInstance->GetGuildManager()->SetGuildInfo(Guild);
	return false;
}

bool Handle_CREATE_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildCreateResponse& pkt)
{
	return false;
}

bool Handle_ADD_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildAddResponse& pkt)
{
	return false;
}

/* 길드 탈퇴 */
bool Handle_REMOVE_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildRemoveResponse& pkt)
{
	if (pkt.success())
	{
		/* 유저 길드 초기화 */
		FGuildResult Guild;

		GameInstance->GetGuildManager()->SetGuildInfo(Guild);
	}
	return false;
}

/* 길드 삭제 */
bool Handle_DELETE_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildDeleteResponse& pkt)
{
	/* TODO : ExistingGuildListUI에서 길드 삭제 */
	if (pkt.success())
	{	
		/* 유저 길드 초기화 */
		FGuildResult Guild;

		GameInstance->GetGuildManager()->SetGuildInfo(Guild);
	}

	return false;
}



bool Handle_ACCEPT_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildAcceptResponse& pkt)
{
	return false;
}

bool Handle_INVITE_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildInviteResponse& pkt)
{
	return false;
}

bool Handle_CHANGE_NAME_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildChangeNameResponse& pkt)
{
	return false;
}

bool Handle_CHANGE_RANK_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildChangeRankResponse& pkt)
{
	return false;
}

bool Handle_CONNECT_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildConnectResponse& pkt)
{
	return false;
}

bool Handle_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildResponse& pkt)
{
	return false;
}
