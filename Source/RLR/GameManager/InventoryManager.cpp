// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/InventoryManager.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"


void UInventoryManager::AddItem(FItemData NewItem)
{
	if (NewItem == FItemData::EmptyItemData)
	{
		DEBUG_LOG("Add Item Warning Message. NewItem is empty.");
		return;
	}
	

	ItemData.Add(NewItem.ITEM_SEQ, NewItem);
	OnUpdateInventoryManager.Broadcast();
}

FItemData UInventoryManager::GetItem(int32 Id)
{
	
	if (ItemData.Contains(Id))
	{
		return ItemData[Id];
	}
	return FItemData();
}

void UInventoryManager::RemoveItem(int32 Id)
{
	if (ItemData.Contains(Id))
	{
		FItemData RemoveItem;
		ItemData.RemoveAndCopyValue(Id, RemoveItem);
		OnUpdateInventoryManager.Broadcast();
	}
}

void UInventoryManager::ChangeItemSlot(int32 Item_Seq, int32 NewSlotIndex)
{
	if (ItemData.Contains(Item_Seq))
	{
		ItemData[Item_Seq].ITEM_SLOT_IDX = NewSlotIndex;
	}
}

void UInventoryManager::SetGold(int32 NewGold)
{
	Gold = NewGold;
	OnUpdateGoldAndCash.Broadcast();
}

void UInventoryManager::SetPlatinum(int32 NewPlatinum)
{
	Platinum = NewPlatinum;
	OnUpdateGoldAndCash.Broadcast();
}

void UInventoryManager::SetCopper(int32 NewCopper)
{
	Copper = NewCopper;
	OnUpdateGoldAndCash.Broadcast();
}

void UInventoryManager::SetSilver(int32 NewSilver)
{
	Silver = NewSilver;
	OnUpdateGoldAndCash.Broadcast();
}

void UInventoryManager::GetItemList(TArray<FItemData>& ItemArray)
{
	ItemData.GenerateValueArray(ItemArray);
}
