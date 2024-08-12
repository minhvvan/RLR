// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientPacketHandler.h"


bool Handle_ATTACK_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::AttackResponsePacket& pkt);

bool Handle_MOVE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::MoveResponsePacket& pkt);
bool Handle_MOVE_BROADCAST(TSharedPtr<PacketSession>& session, Protocol::MoveBroadcastPacket& pkt);

bool Handle_MONSTER_MOVE_REQUEST(TSharedPtr<PacketSession>& session, Protocol::MonsterMoveRequestPacket& pkt);
bool Handle_MONSTER_ATTACK_REQUEST(TSharedPtr<PacketSession>& session, Protocol::MonsterAttackRequestPacket& pkt);
bool Handle_DAMAGE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::DamageResponsePacket& pkt);
bool Handle_MONSTER_STATUS_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::MonsterStatusBroadcastPacket& pkt);