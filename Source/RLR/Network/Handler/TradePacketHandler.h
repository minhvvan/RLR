// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientPacketHandler.h"


bool Handle_TRADE_USER_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_TradeUserResponse& pkt);
bool Handle_TRADE_STATE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_TradeStateResponse& pkt);
bool Handle_TRADE_COMPLETE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_TradeCompleteResponse& pkt);
