// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Storage/StorageUI.h"
#include "UI/InGame/Storage/StorageTab.h"
#include "UI/InGame/Popup/GoodsMessageBox.h"
#include "UI/InGame/Inventory/ItemInformation.h"
#include "UI/InGame/Popup/ItemCountMessageBox.h"
#include "UI/Components/WidgetSwitcherButton.h"
#include "Structs/ItemStructs.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Blueprint/WidgetTree.h"
#include "RLR.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/GameplayTagManager.h"


void UStorageUI::NativeConstruct()
{
	Super::NativeConstruct();

	//BtnBox에 존재하는 WidgetSwitcherBtn 저장
	TabButtons.Empty();
	WidgetTree->GetChildWidgets(BtnBox, TabButtons);

	Init();

	BtnDeposit->OnClicked.AddUniqueDynamic(this, &UStorageUI::OnDepositClicked);
	BtnWithdraw->OnClicked.AddUniqueDynamic(this, &UStorageUI::OnWithdrawClicked);
}

void UStorageUI::Init()
{
	MaxStoragePageNum = TabButtons.Num();

	TArray<TArray<FItemData>> items;
	items.SetNum(MaxStoragePageNum);
	for (int i = 0; i < MaxStoragePageNum; i++)
	{
		items[i].SetNum(MaxStorageSlotNum);
	}

	SetStorageAllItems(items);
}


//창고 Open시 모든 아이템 Slot 설정
void UStorageUI::SetStorageAllItems(const TArray<TArray<FItemData>>& StorageItems)
{
	Items = StorageItems;
	SetUnLockedPageNum();
	RefreshUI();
}

void UStorageUI::SetUnLockedPageNum()
{
	UnLockedPageNum = Items.Num();

	for (int i = 0; i < MaxStoragePageNum; i++)
	{
		if (i < UnLockedPageNum) TabButtons[i]->SetIsEnabled(true);
		else TabButtons[i]->SetIsEnabled(false);
	}
}

void UStorageUI::OpenUI()
{
	GetInventoryManager()->OnInventorySlotClickedDelegate.BindUFunction(this, FName("InventorySlotClicked"));
	GetInventoryManager()->OnInventorySlotShiftClickedDelegate.BindUFunction(this, FName("InventorySlotShiftClicked"));
	Super::OpenUI();
}

void UStorageUI::CloseUI()
{
	GetInventoryManager()->OnInventorySlotClickedDelegate.Clear();
	GetInventoryManager()->OnInventorySlotShiftClickedDelegate.Clear();
	Super::CloseUI();
}

void UStorageUI::InventorySlotClicked(const FItemData& Item)
{
	SendPktInventoryToStorage(Item, Item.QUANTITY);
}

void UStorageUI::InventorySlotShiftClicked(const FItemData& Item)
{
	auto UIManager = GetUIManager();
	if (!UIManager)
	{
		RLR_LOG(LogRLR, Log, TEXT("UIManager is nullptr"));
		return;
	}

	auto messageBox = UIManager->GetSubUI<UItemCountMessageBox>(RLRTAG.UI_Popup_ItemCountMessageBox);
	if (!messageBox)
	{
		RLR_LOG(LogRLR, Log, TEXT("messageBox is nullptr"));
		return;
	}

	messageBox->OpenUI();
	messageBox->SetItemData(Item);
	messageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, FName("InventoryToStorageMessageBoxCallback"));
}

void UStorageUI::SetSlotItem(int TabIdx, int slotIdx, const FItemData& Item)
{
	Items[TabIdx][slotIdx] = Item;
	UStorageTab* tab = Cast<UStorageTab>(WidgetSwitcher->GetWidgetAtIndex(TabIdx));
	if (!tab)
	{
		RLR_LOG(LogRLR, Log, TEXT("StorageTab is nullptr"));
		return;
	}

	tab->SetSlotItemData(Item, slotIdx);
}

void UStorageUI::SetBalance(int Balance)
{
	TxtBalance->SetText(FText::AsNumber(Balance));
}

void UStorageUI::RefreshUI()
{
	for (int i = 0; i < Items.Num(); i++)
	{
		UStorageTab* CurrentTab = Cast<UStorageTab>(WidgetSwitcher->GetWidgetAtIndex(i));
		if (!CurrentTab)
		{
			RLR_LOG(LogRLR, Log, TEXT("StorageTab 형식 불일치"));
			continue;
		}

		CurrentTab->UpdateAllItem(Items[i]);
	}
}

void UStorageUI::OnDepositClicked()
{
	UGoodsMessageBox* messageBox = GetSubUI<UGoodsMessageBox>(RLRTAG.UI_Popup_GoodsMessageBox);
	if (!messageBox)
	{
		RLR_LOG(LogRLR, Log, TEXT("messageBox is nullptr"));
		return;
	}

	messageBox->OpenUI();
	messageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, FName("RequestDeposit"));
}

void UStorageUI::OnWithdrawClicked()
{
	UGoodsMessageBox* messageBox = GetSubUI<UGoodsMessageBox>(RLRTAG.UI_Popup_GoodsMessageBox);
	if (!messageBox)
	{
		RLR_LOG(LogRLR, Log, TEXT("messageBox is nullptr"));
		return;
	}

	messageBox->OpenUI();
	messageBox->SetMessageText(TEXT("창고로 옮길 개수를 입력하세요."));
	messageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, FName("RequestDeposit"));
}

void UStorageUI::RequestDeposit(class UMessageBoxUI* MessageBox)
{
	UGoodsMessageBox* messageBox = Cast<UGoodsMessageBox>(MessageBox);
	if (!messageBox)
	{
		RLR_LOG(LogRLR, Log, TEXT("messageBox is nullptr"));
		return;
	}

	SendPktGoods(true, messageBox->GetAmount());

	messageBox->OnConfirmButtonClickedDelegate.Unbind();
	RLR_LOG(LogRLR, Log, TEXT("req deposit %d"), messageBox->GetAmount());
}

void UStorageUI::RequestWithdraw(class UMessageBoxUI* MessageBox)
{
	UGoodsMessageBox* messageBox = Cast<UGoodsMessageBox>(MessageBox);
	if (!messageBox)
	{
		RLR_LOG(LogRLR, Log, TEXT("messageBox is nullptr"));
		return;
	}

	SendPktGoods(false, messageBox->GetAmount());

	messageBox->OnConfirmButtonClickedDelegate.Unbind();
	RLR_LOG(LogRLR, Log, TEXT("req withdraw %d"), messageBox->GetAmount());
}

void UStorageUI::InventoryToStorageMessageBoxCallback(UMessageBoxUI* MessageBox)
{
	UItemCountMessageBox* messageBox = Cast<UItemCountMessageBox>(MessageBox);
	if (!messageBox)
	{
		RLR_LOG(LogRLR, Log, TEXT("messageBox is nullptr"));
		return;
	}

	SendPktInventoryToStorage(messageBox->GetItemData(), messageBox->GetItemCount());
}

//pkt 전송 함수
void UStorageUI::SendPktInventoryToStorage(const FItemData& Item, int Amount)
{
	//TODO: pkt 전송(itemID? seq?, count)
	//NetworkManager->SendPkt
	//callback에서는 inventory 개수만큼 제외 + storage에 추가(SetSlotItem사용)

	//Test
	//==========================================================================
	GetInventoryManager()->RemoveItem(Item.ITEM_ID, Amount);

	auto tempItem = Item;
	tempItem.QUANTITY = Amount;
	SetSlotItem(WidgetSwitcher->ActiveWidgetIndex, 0, tempItem);

	RLR_LOG(LogRLR, Log, TEXT("Item: %d, %d"), Item.ITEM_ID, Item.QUANTITY);
	//==========================================================================
}

void UStorageUI::SendPktGoods(bool bDeposit, int Amount)
{
	//Callback에서 SetBalance 사용
	if (bDeposit)
	{
		//TODO: 인벤 -> 창고 pkt 전송
	}
	else
	{
		//TODO: 창고 -> 인벤 pkt 전송
	}
}
