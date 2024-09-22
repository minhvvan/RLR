// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Trade/TradeUI.h"
#include "UI/InGame/Trade/TradeList.h"
#include "UI/InGame/Trade/TradeListSlot.h"
#include "UI/InGame/Trade/TradeListElement.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/NetworkManager.h"

#include "Structs/ItemStructs.h"
#include "Structs/PlayerStructs.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void UTradeUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTradeUI::Init()
{
	Super::Init();

	MyTradeList->Init();
	TargetPlayerTradeList->Init();
	OfferButton->OnClicked.AddUniqueDynamic(this, &UTradeUI::SendLockTrade);
	ConfirmButton->OnClicked.AddUniqueDynamic(this, &UTradeUI::SendConfirmTrade);
	AddGoldButton->OnClicked.AddUniqueDynamic(this, &UTradeUI::OnClickedAddGoldButton);
}

void UTradeUI::RefreshUI()
{
	Super::OpenUI();
	MyTradeList->RefreshUI();
	TargetPlayerTradeList->RefreshUI();
}

void UTradeUI::OpenUI()
{
	Super::OpenUI();
	Clear();

	/*
		개인 거래 UI가 열렸을 때, 인벤토리에서 아이템을 누르면 아이템 올라가게 이벤트를 추가해준다.
	*/
	GetInventoryManager()->OnInventorySlotClickedDelegate.BindUFunction(this, FName("SendAddTradeItemBySelf"));
}

void UTradeUI::Clear()
{
	Super::Clear();
	MyTradeList->Clear();
	TargetPlayerTradeList->Clear();
	MyGoldText->SetText(FText());
	TargetGoldText->SetText(FText());
	SetMyTradeState(ETradeState::NORMAL);
	SetTargetTradeState(ETradeState::NORMAL);
}

void UTradeUI::CloseUI()
{
	Super::CloseUI();

	/*
	*	만약 거래 중인 상대가 존재한다면,
		개인 거래 UI를 닫을 때, 상대방한테 거래가 취소되었다는 메시지를 줘야 한다.
	*/
	SendCancelTradePacket();
	GetInventoryManager()->OnInventorySlotClickedDelegate.Clear();
}

void UTradeUI::SendAddTradeItemBySelf(const FItemData& NewTradeItem, int32 Quantity)
{
	/*
	*	TODO
		아이템을 올리겠냐고 확인 메시지 띄워주고 갯수 입력 받기
	*/
	{

	}

	GetNetworkManager()->SendAddTradeItem(NewTradeItem, Quantity);
}

void UTradeUI::SendAddTradeCurrencyBySelf(int32 Amount)
{
	GetNetworkManager()->SendAddTradeCurrency(Amount);
}

void UTradeUI::SendRemoveTradeItemBySelf(const FItemData& NewTradeItem, int32 Quantity)
{
	GetNetworkManager()->SendRemoveTradeItem(NewTradeItem, Quantity);
}

void UTradeUI::HandleAddTradeItemByTarget(const FItemData& NewTradeItem)
{
	/*
		상대방이 아이템을 추가했다는 패킷 받았을 때 핸들. 
	*/
	TargetPlayerTradeList->AddTradeItem(NewTradeItem);
}

void UTradeUI::HandleAddTradeItemBySelf(const FItemData& NewTradeItem)
{
	/*
		내가 아이템을 추가했다는 패킷 받았을 때 핸들.
	*/
	MyTradeList->AddTradeItem(NewTradeItem);
}

void UTradeUI::HandleUpdateTradeCurrencyBySelf(int32 Amount)
{
	MyGoldText->SetText(FText::FromString(FString::FromInt(Amount)));
}

void UTradeUI::HandleUpdateCurrencyByTarget(int32 Amount)
{
	TargetGoldText->SetText(FText::FromString(FString::FromInt(Amount)));
}

void UTradeUI::HandleRemoveTradeItemByTarget(int32 ItemID)
{
	/*
		상대방이 아이템을 제거했다는 패킷 받았을 때 핸들.
	*/
	TargetPlayerTradeList->RemoveTradeItem(ItemID);
}

void UTradeUI::HandleRemoveTradeItemBySelf(int32 ItemID)
{
	/*
		내가 아이템을 제거했다는 패킷 받았을 때 핸들.
	*/
	MyTradeList->RemoveTradeItem(ItemID);
}

void UTradeUI::HandleLockTradeBySelf()
{
	/*
		내가 거래 잠금을 했을 때 핸들
	*/
}

void UTradeUI::HandleUnLockTradeBySelf()
{
	/*
		내가 거래 잠금 해제 했을 때 핸들
	*/
}

void UTradeUI::HandleLockTradeByTarget()
{
	/*
	*	상대방이 거래 잠금 했을 때 핸들
	*/
}

void UTradeUI::HandleUnLockTradeByTarget()
{
	/*
		상대방이 거래 잠금 해제 했을 때 핸들
	*/
}

void UTradeUI::SendLockTrade()
{
	GetNetworkManager()->SendLockTrade();
}

void UTradeUI::SendUnLockTrade()
{
	GetNetworkManager()->SendUnLockTrade();
}

void UTradeUI::SendConfirmTrade()
{
	GetNetworkManager()->SendConfirmTrade();
}

void UTradeUI::SendCancelTradePacket()
{
	/*
		상대방한테 거래가 취소되었다는 패킷을 보낸다.
	*/

	GetNetworkManager()->SendCancelTrade();
	CloseUI();
}

void UTradeUI::HandleTradeCanceledByTarget()
{
	/*
		상대방이 거래를 취소 했을 때 받는 패킷 핸들.
	*/
	{
		//TODO
		//거래가 취소 되었다는 알림 UI를 띄운다.
	}
	CloseUI();
}

void UTradeUI::OnClickedAddGoldButton()
{
	/*
		얼마나 입력할지 수량 입력 박스 띄우기
	*/

}

void UTradeUI::SetMyTradeState(ETradeState TradeState)
{
	MyTradeState = TradeState;
}

void UTradeUI::SetTargetTradeState(ETradeState TradeType)
{
	TargetTradeState = TradeType;
}

