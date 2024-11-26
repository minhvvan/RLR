// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Storage/StorageUI.h"
#include "UI/InGame/Storage/StorageTab.h"
#include "UI/InGame/Popup/GoodsMessageBox.h"
#include "UI/InGame/Inventory/ItemInformation.h"
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

	SetStorageItems(items);
}


//창고 Open시 모든 아이템 Slot 설정
void UStorageUI::SetStorageItems(const TArray<TArray<FItemData>>& StorageItems)
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
	GetInventoryManager()->OnInventorySlotClickedDelegate.BindUFunction(this, FName("AddItem"));
	Super::OpenUI();
}

void UStorageUI::CloseUI()
{
	GetInventoryManager()->OnInventorySlotClickedDelegate.Clear();
	Super::CloseUI();
}

void UStorageUI::AddItem(const FItemData& Item)
{
	//TODO: 현재 열려있는 tab에 추가 pkt전송(tabIdx, item_id)
	SetSlotItem(WidgetSwitcher->GetActiveWidgetIndex(), Item.ITEM_SLOT_IDX, Item);
	auto InventoryManager = GetInventoryManager();
	if (!InventoryManager)
	{
		RLR_LOG(LogRLR, Log, TEXT("InventoryManager is nullptr"));
		return;
	}

	//Inventory에서 아이템 제거
	InventoryManager->RemoveItem(Item.ITEM_ID);

	//close ItemInfo
	UItemInformation* ItemInfo = GetUIManager()->GetSubUI<UItemInformation>(RLRTAG.UI_ItemInfomation);
	if (ItemInfo) ItemInfo->CloseUI();
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

	//TODO: 입금 pkt 전송 messageBox->GetAmount()
	//Callback에서 SetBalance 사용

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

	//TODO: 출금 pkt 전송 messageBox->GetAmount()
	//Callback에서 SetBalance 사용

	messageBox->OnConfirmButtonClickedDelegate.Unbind();
	RLR_LOG(LogRLR, Log, TEXT("req withdraw %d"), messageBox->GetAmount());
}
