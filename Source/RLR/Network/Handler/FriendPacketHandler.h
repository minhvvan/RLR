// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientPacketHandler.h"

bool Handle_INFO_FRIEND_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_StatusResponsePacket& pkt);

bool Handle_FRIEND_CONNECT_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_StatusResponsePacket& pkt);