// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/GuildPacketHandler.h"


bool Handle_INFO_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildinfoResponse& pkt)
{
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

bool Handle_REMOVE_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildRemoveResponse& pkt)
{
	return false;
}

bool Handle_DELETE_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildDeleteResponse& pkt)
{
	return false;
}



bool Handle_ACCEPT_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::CS_GuildAcceptResponse& pkt)
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
