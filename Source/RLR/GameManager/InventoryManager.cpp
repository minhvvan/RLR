// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/InventoryManager.h"


void UInventoryManager::AddItem(FItemData NewItem)
{

	//임시코드. 나중에는 서버에서 보내주는 값으로 해결할 것.
	NewItem.ITEM_SLOT_IDX = ItemKey;
	NewItem.ITEM_ID = ItemKey;
	ItemData.Add(ItemKey, NewItem);
	ItemKey++;
	//


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

void UInventoryManager::SetSilber(int32 NewSilber)
{
	Silber = NewSilber;
	OnUpdateGoldAndCash.Broadcast();
}

void UInventoryManager::GetItemList(TArray<FItemData>& ItemArray)
{
	ItemData.GenerateValueArray(ItemArray);
}
