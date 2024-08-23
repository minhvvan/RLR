// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientPacketHandler.h"


bool Handle_STATUS_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_StatusResponsePacket& pkt);
bool Handle_INVENTORY_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_InventoryResponsePacket& pkt);
bool Handle_MAP_INFO_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_MapMonsterInfoResponsePacket& pkt);
bool Handle_GET_SKILL_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_GetSkillResponsePacket& pkt);
bool Handle_CHANNEL_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_ChannelResponsePacket& pkt);
bool Handle_NPC_INFO_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_NPCInfoResponse& pkt);
bool Handle_USER_QUEST_INFO_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_UserQuestInfoResponse& pkt);