// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Storage/StorageUI.h"
#include "UI/InGame/Storage/StorageTab.h"
#include "UI/InGame/Inventory/ItemInformation.h"
#include "UI/InGame/Popup/ItemCountMessageBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/HorizontalBox.h"
#include "Blueprint/WidgetTree.h"
#include "RLR.h"
#include "GameManager/UIManager.h"
#include "GameManager/StorageManager.h"


void UStorageUI::NativeConstruct()
{
	Super::NativeConstruct();

	//BtnBox에 존재하는 WidgetSwitcherBtn 저장
	TabButtons.Empty();
	WidgetTree->GetChildWidgets(BtnBox, TabButtons);

	if (!StorageManager) StorageManager = GetStorageManager();

	for (int i = 0;i < WidgetSwitcher->GetNumWidgets(); i++)
	{
		auto storageTab = Cast<UStorageTab>(WidgetSwitcher->GetChildAt(i));
		if (!storageTab) continue;
		
		storageTab->SetPageNum(i);
	}
	
	SetStorageAllItems();
}

//창고 Open시 모든 아이템 Slot 설정
void UStorageUI::SetStorageAllItems()
{
	SetUnLockedPageNum();
	RefreshUI();
}

void UStorageUI::SetUnLockedPageNum()
{
	if (!StorageManager) StorageManager = GetStorageManager();
	auto items = StorageManager->GetUserStorageItems();

	for (int i = 0; i < MaxStorageTabNum; i++)
	{
		//TODO: 창고 확장 기능 추가 예정
		if (i < items.Num()) TabButtons[i]->SetIsEnabled(true);
		else TabButtons[i]->SetIsEnabled(false);
	}
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
	messageBox->OnConfirmButtonClickedDelegate.Clear();
	messageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, FName("InventoryToStorageMessageBoxCallback"));
}

void UStorageUI::SetSlotItem(int TabIdx, int slotIdx, const FItemData& Item) const
{
	UStorageTab* tab = Cast<UStorageTab>(WidgetSwitcher->GetWidgetAtIndex(TabIdx));
	if (!tab)
	{
		RLR_LOG(LogRLR, Log, TEXT("StorageTab is nullptr"));
		return;
	}

	tab->SetSlotItemData(Item, slotIdx);
}

int UStorageUI::GetCurrentPage() const
{
	return WidgetSwitcher->GetActiveWidgetIndex();
}

void UStorageUI::RefreshUI()
{
	if (!StorageManager) StorageManager = GetStorageManager();
	auto items = StorageManager->GetUserStorageItems();
	for (int i = 0; i < items.Num(); i++)
	{
		UStorageTab* CurrentTab = Cast<UStorageTab>(WidgetSwitcher->GetWidgetAtIndex(i));
		if (!CurrentTab)
		{
			RLR_LOG(LogRLR, Log, TEXT("StorageTab 형식 불일치"));
			continue;
		}

		CurrentTab->UpdateAllItem(items[i], UITag);
	}
}

void UStorageUI::InventoryToStorageMessageBoxCallback(class UMessageBoxUI* MessageBox)
{
	UItemCountMessageBox* messageBox = Cast<UItemCountMessageBox>(MessageBox);
	if (!messageBox)
	{
		RLR_LOG(LogRLR, Log, TEXT("messageBox is nullptr"));
		return;
	}

	if (!StorageManager) StorageManager = GetStorageManager();
	StorageManager->SendPktMoveItemInventoryToUserStorage(messageBox->GetItemData(), messageBox->GetItemCount(), WidgetSwitcher->GetActiveWidgetIndex());
}
