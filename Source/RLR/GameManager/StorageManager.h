// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RLRStruct.h"
#include "StorageManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStorageAllItemUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoragePageItemUpdated, int, PageIndex);

UCLASS()
class RLR_API UStorageManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	TArray<TArray<FItemData>> UserStorageItems;
	TArray<TArray<FItemData>> PlayerStorageItems;
	int UnLockedPageNum = 1;
	const int MaxStoragePageNum = 5;
	const int MaxStorageSlotNum = 50;

public:
	FOnStorageAllItemUpdated OnUserStorageAllItemUpdated;
	FOnStoragePageItemUpdated OnUserStoragePageItemUpdated;

	FOnStorageAllItemUpdated OnPlayerStorageAllItemUpdated;
	FOnStoragePageItemUpdated OnPlayerStoragePageItemUpdated;

public:
	const TArray<TArray<FItemData>>& GetUserStorageItems();
	const TArray<FItemData>& GetUserStorageItemPage(int page);

	//Set ItemData
	void SetUserStorageAllItems(const TArray<TArray<FItemData>>& StorageItems);
	void SetUserStorageItemPage(int PageIndex, const TArray<FItemData>& StorageItems);
	void SetUserStorageItem(int PageIndex, int SlotIdx, const FItemData& Item);

	void SetPlayerStorageAllItems(const TArray<TArray<FItemData>>& StorageItems);
	void SetPlayerStorageItemPage(int PageIndex, const TArray<FItemData>& StorageItems);
	void SetPlayerStorageItem(int PageIndex, int SlotIdx, const FItemData& Item);

	//Get ItemData
	void RequestGetUserStorageItems();
	void RequestGetPlayerStorageItems();

	//Swap in Same Storage
	void SwapStorageItems(int PageIndex, int lhsSlotIndex, const FItemData& lhs, int rhsSlotIndex, const FItemData& rhs, ESlotType SlotType);

	//Inventory <-> Storage
	void SendPktMoveItemInventoryToStorage(const FItemData& Item, int Amount, ESlotType SlotType, int StorageSLotIndex=-1, int InventorySlotIndex = -1);
	void SendPktMoveItemStorageToInventory(const FItemData& Item, int Amount, ESlotType SlotType, int StorageSLotIndex=-1, int InventorySlotIndex = -1);

	//Storage <-> Storage
	void SendPktSwapStorageItem(const FItemData& PlayerStorageItem, const FItemData& UserStorageItem, int PlayerStorageIndex, int UserStorageIndex);

private:
	void SendPktMoveItemInventoryToPlayerStorage(const FItemData& Item, int Amount, int StorageSLotIndex=-1, int InventorySlotIndex = -1);
	void SendPktMoveItemPlayerStorageToInventory(const FItemData& Item, int Amount, int StorageSLotIndex=-1, int InventorySlotIndex = -1);

	void SendPktMoveItemInventoryToUserStorage(const FItemData& Item, int Amount, int StorageSLotIndex=-1, int InventorySlotIndex = -1);
	void SendPktMoveItemUserStorageToInventory(const FItemData& Item, int Amount, int StorageSLotIndex=-1, int InventorySlotIndex = -1);
};
