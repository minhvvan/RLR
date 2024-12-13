#pragma once
#include "CoreMinimal.h"
#include "GameManager/GameManager.h"
#include "GameManager/EnhanceManager.h"
#include "ClientPacketHandler.h"

bool Handle_ENHANCE_SUCCESS_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_EnhanceSuccessResponse& pkt);
bool Handle_ENHANCE_FAILURE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_EnhanceFailureResponse& pkt);
