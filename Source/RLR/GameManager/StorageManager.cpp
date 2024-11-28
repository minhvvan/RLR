// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/StorageManager.h"
#include "Structs/ItemStructs.h"

void UStorageManager::SetStorageAllItems(const TArray<TArray<FItemData>>& StorageItems)
{
	Items = StorageItems;
	OnStorageAllItemUpdated.Broadcast(Items);
}

void UStorageManager::SendPktInventoryToStorage(const FItemData& Item, int Amount)
{
}

void UStorageManager::SendPktGoods(bool bDeposit, int Amount)
{
}
