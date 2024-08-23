// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientPacketHandler.h"


bool Handle_ATTACK_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_AttackResponsePacket& pkt);

bool Handle_MOVE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_MoveResponsePacket& pkt);
bool Handle_MOVE_BROADCAST(TSharedPtr<PacketSession>& session, Protocol::SC_MoveBroadcastPacket& pkt);

bool Handle_MONSTER_MOVE_REQUEST(TSharedPtr<PacketSession>& session, Protocol::SC_MonsterMoveRequestPacket& pkt);
bool Handle_MONSTER_ATTACK_REQUEST(TSharedPtr<PacketSession>& session, Protocol::SS_MonsterAttackRequestPacket& pkt);
bool Handle_DAMAGE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SS_DamageResponsePacket& pkt);
bool Handle_MONSTER_STATUS_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_MonsterStatusBroadcastPacket& pkt);
bool Handle_MONSTER_DIE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::MonsterDieBroadcast& pkt);