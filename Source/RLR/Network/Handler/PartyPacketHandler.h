// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientPacketHandler.h"

bool Handle_PARTY_MAP_INFO_REQUEST(TSharedPtr<PacketSession>& session, Protocol::SC_PartyMapInfoRequest& pkt);
bool Handle_CREATE_PARTY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_CreatePartyResponse& pkt);
bool Handle_PARTY_STATUS_UPDATE(TSharedPtr<PacketSession>& session, Protocol::SC_PartyStatusUpdate& pkt);
bool Handle_JOIN_PARTY_RESP0NSE(TSharedPtr<PacketSession>& session, Protocol::SC_JoinPartyResponse& pkt);
bool Handle_LEAVE_PARTY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_LeavePartyResponse& pkt);
bool Handle_EXILE_PARTY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_ExilePartyResponse& pkt);
bool Handle_REQUEST_PARTY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_RequestPartyResponse& pkt);