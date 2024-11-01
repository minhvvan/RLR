// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/FriendPacketHandler.h"
#include "Structs/UtilStructs.h"
#include "GameManager/GameManager.h"
#include "GameManager/FriendManager.h"


bool Handle_INFO_FRIEND_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_FriendInfoResponse& pkt)
{
	TArray<FFriendGroupResult> groupData;

	for (int32 i = 0; i < pkt.groups_size(); i++) {
		FFriendGroupResult groupDatum;
		groupDatum.MakeGroupData(pkt.groups().at(i));
		groupData.Add(groupDatum);
	}

    GameInstance->GetFriendManager()->SetFriendData(groupData);
    return false;
}

bool Handle_REQUEST_FRIEND_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_RequestFriendResponse& pkt)
{
	GameInstance->GetFriendManager()->SetRequestFriendData(pkt.friendseq(), UTF8_TO_TCHAR(pkt.friendname().c_str()));
	return false;
}

bool Handle_FRIEND_CONNECT_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_FriendConnectResponse& pkt)
{
    return false;
}