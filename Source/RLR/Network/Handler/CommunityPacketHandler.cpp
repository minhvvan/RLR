// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/CommunityPacketHandler.h"
#include "ClientPacketHandler.h"


bool Handle_OTHER_STATUS_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_OtherStatusResponse& pkt) {
	return false;
}
bool Handle_CONTENT_COMMUNITY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_CommunityContentResponse& pkt) {
	return false;
}
bool Handle_ACCEPT_COMMUNITY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_CommunityAcceptResponse& pkt) {
	return false;
}
bool Handle_INVITE_COMMUNITY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_CommunityInviteResponse& pkt) {
	return false;
}
bool Handle_LIST_COMMUNITY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_CommunityListResponse& pkt) {
	return false;
}
bool Handle_KICK_COMMUNITY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_CommunityKickResponse& pkt) {
	return false;
}
bool Handle_STATUS_COMMUNITY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_CommunityStateResponse& pkt) {
	return false;
}
bool Handle_ACCEPT_CONTENT_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_ContentAcceptResponse& pkt) {
	return false;
}
bool Handle_CANCEL_CONTENT_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_ContentCancelResponse& pkt) {
	return false;
}

bool Handle_FAIL_CONTENT_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_ContentFailResponse& pkt)
{
	return false;
}
