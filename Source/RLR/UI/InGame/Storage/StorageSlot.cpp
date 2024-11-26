// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Storage/StorageSlot.h"
#include "Components/Image.h"
#include "UI/BaseDragDropOperation.h"
#include "GameManager/InventoryManager.h"
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

	//TODO: 인벤토리로 아이템 빼기 pkt 전송(pageIdx, slot_idx?(item_id?))
	auto InventoryManager = GetInventoryManager();
	if (!InventoryManager)
	{
		RLR_LOG(LogRLR, Log, TEXT("InventoryManager is nullptr"));
		return result;
	}

	const FItemData& itemData = GetItemData();
	if (itemData == FItemData::EmptyItemData)
	{
		RLR_LOG(LogRLR, Log, TEXT("ItemData is EmptyItemData"));
		return result;
	}

	InventoryManager->AddItem(itemData);
	Clear();

	return result;
}

void UStorageSlot::RefreshUI()
{
	auto itemData = GetItemData();
	UTexture2D* itemImage = GetItemResourceData().ItemImage;

	if (itemData == FItemData::EmptyItemData)
	{
		itemImage = GetDefaultSlotImage();
	}

	SlotImage->SetBrushFromTexture(itemImage);
}
