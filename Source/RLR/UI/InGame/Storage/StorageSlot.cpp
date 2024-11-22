// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Storage/StorageSlot.h"
#include "Components/Image.h"

void UStorageSlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	UStorageSlot* itemSlot = Cast<UStorageSlot>(ListItemObject);

	if (itemSlot)
	{
		SetItemData(const_cast<FItemData&>(itemSlot->GetItemData()));
		RefreshUI();
	}
}

void UStorageSlot::RefreshUI()
{
	auto itemData = GetItemData();
	UTexture2D* itemImage = GetItemResourceData().ItemImage;

	if (itemData == FItemData::EmptyItemData)
	{
		SetIsEnabled(false);
		itemImage = GetDefaultSlotImage();
	}
	else
	{
		SetIsEnabled(true);
	}

	SlotImage->SetBrushFromTexture(itemImage);
}
