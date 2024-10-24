// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientPacketHandler.h"

bool Handle_OTHER_STATUS_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_OtherStatusResponse& pkt);
bool Handle_CONTENT_COMMUNITY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_CommunityContentResponse& pkt);
bool Handle_ACCEPT_COMMUNITY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_CommunityAcceptResponse& pkt);
bool Handle_INVITE_COMMUNITY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_CommunityInviteResponse& pkt);
bool Handle_LIST_COMMUNITY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_CommunityListResponse& pkt);
bool Handle_KICK_COMMUNITY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_CommunityKickResponse& pkt);
bool Handle_STATUS_COMMUNITY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_CommunityStateResponse& pkt);
bool Handle_ACCEPT_CONTENT_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_ContentAcceptResponse& pkt);
bool Handle_CANCEL_CONTENT_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_ContentCancelResponse& pkt);
bool Handle_FAIL_CONTENT_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_ContentFailResponse& pkt);

