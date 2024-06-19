// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/InventoryManager.h"


void UInventoryManager::AddItem(FItemData NewItem)
{

	//임시코드
	NewItem.ITEM_SLOT_IDX = ItemKey;


	ItemKey++;
	ItemData.Add(ItemKey, NewItem);
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

void UInventoryManager::SetCash(int32 NewCash)
{
	Cash = NewCash;
	OnUpdateGoldAndCash.Broadcast();
}

void UInventoryManager::GetItemList(TArray<FItemData>& ItemArray)
{
	ItemData.GenerateValueArray(ItemArray);
}
