// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/TradePacketHandler.h"

#include "UI/InGame/Trade/TradeUI.h"
#include "UI/InGame/Trade/TradeList.h"
#include "UI/InGame/Trade/TradeListSlot.h"
#include "UI/InGame/Trade/TradeListElement.h"
#include "UI/InGame/Popup/ItemCountMessageBox.h"
#include "UI/InGame/Popup/NotificationMessageBox.h"
#include "UI/BaseUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameplayTagManager.h"

#include "Structs/ItemStructs.h"
#include "Structs/PlayerStructs.h"
#include "Structs/UtilStructs.h"

bool Handle_TRADE_USER_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_TradeUserResponse& pkt)
{
	// Todo : 상대 수락 대기화면 
	UTradeUI* TradeUI = Cast<UTradeUI>(GameInstance->GetUIManager()->GetUI(EUIType::TRADE_UI));
	if(IsValid(TradeUI) == false)
		return false;

	TradeUI->HandleTradeUserResponse(pkt);
	return true;
}


bool Handle_TRADE_START_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_TradeStartResponse& pkt)
{
	// Todo : 시작 대기화면 
	UTradeUI* TradeUI = Cast<UTradeUI>(GameInstance->GetUIManager()->GetUI(EUIType::TRADE_UI));
	if (IsValid(TradeUI) == false)
		return false;
	
	TradeUI->HandleTradeStartResponse(pkt);
	return true;
}

bool Handle_TRADE_STATE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_TradeStateResponse& pkt)
{
	// Todo : Trade 창 안에 아이템 재화 업데이트 될 때마다 호출되는 함수
	UTradeUI* TradeUI = Cast<UTradeUI>(GameInstance->GetUIManager()->GetUI(EUIType::TRADE_UI));
	if (IsValid(TradeUI) == false)
		return false;

	TradeUI->HandleTradeStateResponse(pkt);
	return true;
}

bool Handle_TRADE_COMPLETE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_TradeCompleteResponse& pkt)
{
	//Todo : 거래 완료 시 상대 이름, 받은 아이템, 받은 돈 보여주기
	UTradeUI* TradeUI = Cast<UTradeUI>(GameInstance->GetUIManager()->GetUI(EUIType::TRADE_UI));
	if (IsValid(TradeUI) == false)
		return false;

	TradeUI->HandleTradeCompleteResponse(pkt);
	return true;
}
