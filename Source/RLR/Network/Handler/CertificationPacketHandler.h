// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientPacketHandler.h"


bool Handle_LOGIN_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_LoginResponsePacket& pkt);

bool Handle_ENTER_GAME_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_EnterGameResponsePacket& pkt);
bool Handle_CHARACTER_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_UserResponsePacket& pkt);