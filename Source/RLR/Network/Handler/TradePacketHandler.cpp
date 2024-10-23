// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/TradePacketHandler.h"

bool Handle_TRADE_USER_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_TradeUserResponse& pkt)
{
	// Todo : 상대 수락 대기화면 
	return false;
}


bool Handle_TRADE_START_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_TradeStartResponse& pkt)
{
	// Todo : 시작 대기화면 
	return false;
}

bool Handle_TRADE_STATE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_TradeStateResponse& pkt)
{
	// Todo : Trade 창 안에 아이템 재화 업데이트 될 때마다 호출되는 함수
	return false;
}

bool Handle_TRADE_COMPLETE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_TradeCompleteResponse& pkt)
{
	//Todo : 거래 완료 시 상대 이름, 받은 아이템, 받은 돈 보여주기
	return false;
}
