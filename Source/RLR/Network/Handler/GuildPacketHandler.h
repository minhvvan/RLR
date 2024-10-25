// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientPacketHandler.h"

bool Handle_INFO_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildinfoResponse& pkt);
bool Handle_CREATE_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildCreateResponse& pkt);
bool Handle_ADD_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildAddResponse& pkt);
bool Handle_REMOVE_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildRemoveResponse& pkt);
bool Handle_DELETE_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildDeleteResponse& pkt);
bool Handle_ACCEPT_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::CS_GuildAcceptResponse& pkt);
bool Handle_INVITE_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildInviteResponse& pkt);
bool Handle_CHANGE_NAME_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildChangeNameResponse& pkt);
bool Handle_CHANGE_RANK_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildChangeRankResponse& pkt);
bool Handle_CONNECT_GUILD_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GuildConnectResponse& pkt);
