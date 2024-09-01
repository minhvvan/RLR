// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientPacketHandler.h"

/*
	Title
*/

bool Handle_SERVERLIST_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_LoginResponsePacket& pkt);	
bool Handle_LOGIN_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_LoginResponsePacket& pkt);		

/*
	Lobby
*/

//bool Handle_CHARACTERLIST_RESPONSE()	
//bool Handle_CREATE_CHARACTER_RESPONSE()
//bool Handle_Delete_CHARACTER_RESPONSE()
bool Handle_ENTER_GAME_FROM_LOBBY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_EnterGameResponsePacket& pkt);

/*
	InGame
*/
bool Handle_ENTER_GAME_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_EnterGameResponsePacket& pkt);
bool Handle_CHARACTER_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_UserResponsePacket& pkt);