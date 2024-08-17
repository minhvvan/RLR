// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientPacketHandler.h"

bool Handle_ITEM_ADD_REQUEST(TSharedPtr<PacketSession>& session, Protocol::ItemAddRequestPacket& pkt);
bool Handle_ITEM_USE_REQUEST(TSharedPtr<PacketSession>& session, Protocol::ItemUseRequestPacket& pkt);
bool Handle_DROP_REQUEST(TSharedPtr<PacketSession>& session, Protocol::DropRequest& pkt);
bool Handle_EQUIP_INFO_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::EquipInfoResponse& pkt);
bool Handle_EQUIP_CHANGE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::EquipChangeRespnse& pkt);
