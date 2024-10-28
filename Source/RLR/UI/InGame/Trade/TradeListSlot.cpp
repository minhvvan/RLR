// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Trade/TradeListSlot.h"
#include "UI/InGame/Trade/TradeUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"

#include "Structs/ItemStructs.h"

void UTradeListSlot::NativeConstruct()
{
	Super::NativeConstruct();

}

void UTradeListSlot::Init()
{
	Super::Init();
	SetSlotType(ESlotType::TRADE_LIST_SLOT);
}

void UTradeListSlot::RefreshUI()
{
	Super::RefreshUI();

	if (GetItemData() == FItemData::EmptyItemData)
	{
		return;
	}

	SetSlotImage(GetItemResourceData().ItemImage);
}

void UTradeListSlot::Clear()
{
	Super::Clear();
}

FReply UTradeListSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	//비어 있으면 리턴 || 내 슬롯이 아니면 리턴
	if (IsEmpty() == true || GetCanDrag() == false)
	{
		return result;
	}

	const FItemData&  itemData = GetItemData();

	/*
		서버에 거래 리스트에서 아이템이 내려갔다는 패킷을 보낸다.
			1.서버에서 Request 해주면 자기 거래 리스트에서 내려가게 Handle.
			2.상대방한테 거래 리스트에서 내려갔다는 패킷을 보내준다.
	*/
	{
		UTradeUI* TradeUI = Cast<UTradeUI>(GetUIManager()->GetUI(EUIType::TRADE_UI));
		if(IsValid(TradeUI) == false)
			return result;
		TradeUI->SendTradeRemoveItemBySelf(itemData, itemData.QUANTITY);
	}
	return result;
}
