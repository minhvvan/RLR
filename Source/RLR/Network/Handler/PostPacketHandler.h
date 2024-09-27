// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientPacketHandler.h"


bool Handle_POST_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_PostResponse& pkt);
