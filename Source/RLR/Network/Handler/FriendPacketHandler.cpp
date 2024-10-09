// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/FriendPacketHandler.h"


bool Handle_INFO_FRIEND_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_FriendInfoResponse& pkt)
{
    // FriendManager 생성 시 추가
    return false;
}

bool Handle_FRIEND_CONNECT_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_FriendConnectResponse& pkt)
{
    return false;
}
