// Fill out your copyright notice in the Description page of Project Settings.


#include "Structs/CommunicationStructs.h"

void FTradeData::MakeTradeState(Protocol::SC_TradeStateResponse& pkt)
{
	for (int32 i = 0; i < pkt.useritemlist1_size(); i++) {
		FItemData itemData;
		itemData.MakeItemData(pkt.useritemlist1().at(i));
		UserItemList1.Add(itemData);
	}

	UserMoney1 = pkt.totalmoney1();
	UserLockState1 = pkt.lockstate1();

	for (int32 i = 0; i < pkt.useritemlist2_size(); i++) {
		FItemData itemData;
		itemData.MakeItemData(pkt.useritemlist2().at(i));
		UserItemList2.Add(itemData);
	}

	UserMoney2 = pkt.totalmoney2();
	UserLockState2 = pkt.lockstate2();
}
