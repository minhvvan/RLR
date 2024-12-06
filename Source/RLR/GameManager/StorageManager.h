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
	TArray<TArray<FItemData>> Items;
	int UnLockedPageNum = 1;
	const int MaxStoragePageNum = 5;
	const int MaxStorageSlotNum = 50;

public:
	FOnStorageAllItemUpdated OnStorageAllItemUpdated;
	FOnStoragePageItemUpdated OnStoragePageItemUpdated;

public:
	const TArray<TArray<FItemData>>& GetAllItems();
	const TArray<FItemData>& GetItemPage(int page);

	void SetStorageAllItems(const TArray<TArray<FItemData>>& StorageItems);
	void SetStorageItemPage(int PageIndex, const TArray<FItemData>& StorageItems);
	void SetStorageItem(int PageIndex, int SlotIdx, const FItemData& Item);
	
	void RequestGetStorageItems();
	void SwapItems(int TabIdx, int lhsSlotIndex, const FItemData& lhs, int rhsSlotIndex, const FItemData& rhs);
	void SendPktMoveItemInventoryToStorage(const FItemData& Item, int Amount, int PageIndex, int SlotIndex=-1);
	void SendPktMoveItemStorageToInventory(const FItemData& Item, int Amount, int PageIndex, int SlotIndex=-1);
};
