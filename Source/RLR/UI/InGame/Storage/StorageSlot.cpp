// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Storage/StorageSlot.h"
#include "UI/InGame/Popup/ItemCountMessageBox.h"
#include "UI/BaseDragDropOperation.h"
#include "Components/Image.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/UIManager.h"
#include "UI/InGame/Inventory/ItemInformation.h"
#include "RLR.h"

void UStorageSlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	UStorageSlot* itemSlot = Cast<UStorageSlot>(ListItemObject);

	if (itemSlot)
	{
		SetItemData(const_cast<FItemData&>(itemSlot->GetItemData()));
	}
}

bool UStorageSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool bResult = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if (!bResult) return bResult;

	UBaseDragDropOperation* Operation = CheckValidAndType(InOperation, ESlotType::INVENTORY_SLOT);
	if (!Operation)
	{
		RLR_LOG(LogRLR, Log, TEXT("Dropped SameSlot"));
		return bResult;
	}

	if (Operation->DragedSlotType == ESlotType::INVENTORY_SLOT)
	{
		//Inventory->Storage
	}
	else if (Operation->DragedSlotType == ESlotType::STORAGE_ITEM_SLOT)
	{
		//Storage->Storage

		//TODO: InOperation에서 slotIdx받아서 pkt 전송(swap)
		//GetItemData().ITEM_SLOT_IDX
		//Operation->GetItemData().ITEM_SLOT_IDX
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

		SendPktStroageToInventory(itemData, itemData.QUANTITY);
	}

	return result;
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

void UStorageSlot::StorageToInventoryMessageBoxCallback(UMessageBoxUI* MessageBox)
{
	//TODO: 인벤토리로 아이템 빼기 pkt 전송(pageIdx, slot_idx?(item_id?)) + id어떻게 처리??
	UItemCountMessageBox* messageBox = Cast<UItemCountMessageBox>(MessageBox);
	if (!messageBox)
	{
		RLR_LOG(LogRLR, Log, TEXT("messageBox is nullptr"));
		return;
	}

	SendPktStroageToInventory(messageBox->GetItemData(), messageBox->GetItemCount());
}

void UStorageSlot::SendPktStroageToInventory(const FItemData& Item, int Amount)
{
	//TODO: 창고 -> 인벤토리 패킷 전송(pageIdx, slot_idx?(item_id?))
	//callback에서는 inventory 개수만큼 추가 + storage에서 제거(SetSlotItem사용)

	//Test
	//==========================================================================
	{
		FItemData tempItem = GetItemData();
		GetInventoryManager()->AddItem(tempItem);
	}

	{
		FItemData tempItem = GetItemData();
		tempItem.QUANTITY -= Amount;
		SetItemData(tempItem);
	}

	RLR_LOG(LogRLR, Log, TEXT("Item: %d, %d"), Item.ITEM_ID, Item.QUANTITY);
	//==========================================================================
}
