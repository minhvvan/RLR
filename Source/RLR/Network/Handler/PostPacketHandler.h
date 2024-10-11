// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientPacketHandler.h"


bool Handle_POST_GET_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_PostGetResponse& pkt);
bool Handle_POST_SEND_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_PostSendResponse& pkt);