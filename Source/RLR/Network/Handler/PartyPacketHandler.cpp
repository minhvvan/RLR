// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/PartyPacketHandler.h"
#include "GameManager/GameManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/MonsterManager.h"
#include "GameManager/ObjectManager.h"
#include "GameManager/NetworkManager.h"
bool Handle_PARTY_MAP_INFO_REQUEST(TSharedPtr<PacketSession>& session, Protocol::SC_PartyMapInfoRequest& pkt)
{
	GameInstance->GetNetworkManager()->SetMapId(pkt.mapid());
	GameInstance->GetNetworkManager()->SendMapInfoRequest(pkt.partyid());
	return false;
}

bool Handle_CREATE_PARTY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_CreatePartyResponse& pkt)
{
	return false;
}

bool Handle_PARTY_STATUS_UPDATE(TSharedPtr<PacketSession>& session, Protocol::SC_PartyStatusUpdate& pkt)
{
	return false;
}

bool Handle_JOIN_PARTY_RESP0NSE(TSharedPtr<PacketSession>& session, Protocol::SC_JoinPartyResponse& pkt)
{
	return false;
}

bool Handle_LEAVE_PARTY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_LeavePartyResponse& pkt)
{
	return false;
}
