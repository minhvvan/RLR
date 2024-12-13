// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Storage/StorageSlot.h"
#include "UI/InGame/Popup/ItemCountMessageBox.h"
#include "UI/BaseDragDropOperation.h"
#include "Components/Image.h"
#include "GameManager/StorageManager.h"
#include "GameManager/UIManager.h"
#include "UI/InGame/Inventory/ItemInformation.h"
#include "RLR.h"

void UStorageSlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	UStorageSlot* itemSlot = Cast<UStorageSlot>(ListItemObject);

	if (itemSlot)
	{
		auto item = itemSlot->GetItemData();

		PageIndex = itemSlot->PageIndex;
		SetItemData(item);
		SetSlotIndex(itemSlot->GetSlotIndex());
		SetSlotType(itemSlot->SlotType);
	}
}

bool UStorageSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool bResult = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if (!bResult) return bResult;

	UBaseDragDropOperation* Operation = Cast<UBaseDragDropOperation>(InOperation);
	if (!Operation)
	{
		RLR_LOG(LogRLR, Log, TEXT("Dropped SameSlot"));
		return bResult;
	}
	
	UStorageManager* StorageManager = GetStorageManager();
	if (!StorageManager)
	{
		RLR_LOG(LogRLR, Log, TEXT("StorageManager is nullptr"));
		return bResult;
	}

	const auto& recvItem = Operation->GetItemData();
	if (recvItem == FItemData::EmptyItemData)
	{
		RLR_LOG(LogRLR, Log, TEXT("Item is EmptyItem"));
		return bResult;
	}

	const auto& currentSlotItem = GetItemData();
	
	if (Operation->DragedSlotType == ESlotType::STORAGE_INVENTORY_SLOT)
	{
		//Inventory->Storage
		StorageManager->SendPktMoveItemInventoryToStorage(recvItem, recvItem.QUANTITY, SlotType, SlotIndex);
	}
	else if (Operation->DragedSlotType == SlotType)
	{
		//Move Same Storage
		StorageManager->SwapStorageItems(PageIndex, Operation->SlotIndex, recvItem, SlotIndex, currentSlotItem, SlotType);
	}
	else
	{
		if (Operation->DragedSlotType == ESlotType::PLAYER_STORAGE_ITEM_SLOT)
		{
			//Player -> User
			StorageManager->SendPktSwapStorageItem(recvItem, currentSlotItem, Operation->SlotIndex, SlotIndex);
		}
		else if (Operation->DragedSlotType == ESlotType::USER_STORAGE_ITEM_SLOT)
		{
			//User -> Player
			StorageManager->SendPktSwapStorageItem(currentSlotItem, recvItem, SlotIndex, Operation->SlotIndex);
		}
	}

	return bResult;
}

FReply UStorageSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsLeftShiftDown())
	{
		//개수 선택
		auto UIManager = GetUIManager();
		if (!UIManager)
		{
			RLR_LOG(LogRLR, Log, TEXT("UIManager is nullptr"));
			return result;
		}

		auto messageBox = UIManager->GetSubUI<UItemCountMessageBox>(RLRTAG.UI_Popup_ItemCountMessageBox);
		if (!messageBox)
		{
			RLR_LOG(LogRLR, Log, TEXT("messageBox is nullptr"));
			return result;
		}

		const FItemData& itemData = GetItemData();
		if (itemData == FItemData::EmptyItemData)
		{
			RLR_LOG(LogRLR, Log, TEXT("ItemData is EmptyItemData"));
			return result;
		}

		messageBox->OpenUI();
		messageBox->SetMessageText(TEXT("인벤토리로 옮길 아이템 개수를 입력하세요."));
		messageBox->SetItemData(itemData);
		messageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, FName("StorageToInventoryMessageBoxCallback"));
	}
	else
	{
		//전체
		const FItemData& itemData = GetItemData();
		if (itemData == FItemData::EmptyItemData)
		{
			RLR_LOG(LogRLR, Log, TEXT("ItemData is EmptyItemData"));
			return result;
		}

		MoveStorageToInventory(itemData, itemData.QUANTITY);
	}

	return result;
}

void UStorageSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (IsEmpty() == true) return;

	UUIManager* UIManager = GetUIManager();
	if (UIManager == nullptr) return;

	UMainUI* mainUI = UIManager->GetPage<UMainUI>(UIManager->GetActivePageTag());
	if (mainUI == nullptr) return;

	mainUI->OpenSubUINearTargetSlot(this, RLRTAG.UI_ItemInfomation);
}

void UStorageSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	UUIManager* UIManager = GetUIManager();
	if (UIManager == nullptr) return;

	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	UIManager->CloseSubUI(TagManager.UI_ItemInfomation);
}

void UStorageSlot::RefreshUI()
{
	Super::RefreshUI();

	auto itemData = GetItemData();
	UTexture2D* itemImage = GetItemResourceData().ItemImage;

	if (itemData.QUANTITY == 0)
	{
		itemData = FItemData::EmptyItemData;
	}

	if (itemData == FItemData::EmptyItemData)
	{
		itemImage = GetDefaultSlotImage();
	}

	SlotImage->SetBrushFromTexture(itemImage);
}

void UStorageSlot::SetPageNum(int page)
{
	PageIndex = page;
}

int UStorageSlot::GetPageNum() const
{
	return PageIndex;
}

void UStorageSlot::StorageToInventoryMessageBoxCallback(UMessageBoxUI* MessageBox)
{
	UItemCountMessageBox* messageBox = Cast<UItemCountMessageBox>(MessageBox);
	if (!messageBox)
	{
		RLR_LOG(LogRLR, Log, TEXT("messageBox is nullptr"));
		return;
	}

	MoveStorageToInventory(messageBox->GetItemData(), messageBox->GetItemCount());
}

void UStorageSlot::MoveStorageToInventory(const FItemData& Item, int Amount)
{
	UStorageManager* StorageManager = GetStorageManager();
	StorageManager->SendPktMoveItemStorageToInventory(Item, Amount, SlotType, SlotIndex);
}
