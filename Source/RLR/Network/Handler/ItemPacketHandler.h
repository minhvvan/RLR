// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientPacketHandler.h"

bool Handle_ITEM_USE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_ItemUseResponsePacket& pkt);
bool Handle_ADD_ITEM_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_AddItemResponse& pkt);
bool Handle_DROP_REQUEST(TSharedPtr<PacketSession>& session, Protocol::SC_DropRequest& pkt);
bool Handle_EQUIP_INFO_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_EquipInfoResponse& pkt);
bool Handle_EQUIP_CHANGE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_EquipChangeRespnse& pkt);
