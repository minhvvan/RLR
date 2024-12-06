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
		SetSlotType(ESlotType::STORAGE_ITEM_SLOT);
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

	if (Operation->DragedSlotType == ESlotType::INVENTORY_SLOT)
	{
		//Inventory->Storage
		UStorageManager* StorageManager = GetStorageManager();
		if (!StorageManager)
		{
			RLR_LOG(LogRLR, Log, TEXT("StorageManager is nullptr"));
			return bResult;
		}

		auto item = Operation->GetItemData();
		if (item == FItemData::EmptyItemData)
		{
			RLR_LOG(LogRLR, Log, TEXT("Item is EmptyItem"));
			return bResult;
		}

		StorageManager->SendPktMoveItemInventoryToStorage(item, item.QUANTITY, PageIndex, SlotIndex);
	}
	else if (Operation->DragedSlotType == ESlotType::STORAGE_ITEM_SLOT)
	{
		//Storage->Storage
		UStorageManager* StorageManager = GetStorageManager();
		if (!StorageManager)
		{
			RLR_LOG(LogRLR, Log, TEXT("StorageManager is nullptr"));
			return bResult;
		}

		auto recvItem = Operation->GetItemData();
		if (recvItem == FItemData::EmptyItemData)
		{
			RLR_LOG(LogRLR, Log, TEXT("Item is EmptyItem"));
			return bResult;
		}

		auto currentSlotItem = GetItemData();

		StorageManager->SwapItems(PageIndex, Operation->SlotIndex, recvItem, SlotIndex, currentSlotItem);
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
		messageBox->SetMessageText(TEXT("인벤토리로 옮길 개수를 입력하세요."));
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
	//TODO: 인벤토리로 아이템 빼기 pkt 전송(pageIdx, slot_idx?(item_id?)) + id어떻게 처리??
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
	StorageManager->SendPktMoveItemStorageToInventory(Item, Amount, PageIndex, SlotIndex);
}
