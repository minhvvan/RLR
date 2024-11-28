// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RLRStruct.h"
#include "StorageManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStorageAllItemUpdated);

UCLASS()
class RLR_API UStorageManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	TArray<TArray<FItemData>> Items;
	int UnLockedPageNum = 1;

public:
	FOnStorageAllItemUpdated OnStorageAllItemUpdated;

public:
	const TArray<TArray<FItemData>>& GetAllItems();

	void SetStorageAllItems(const TArray<TArray<FItemData>>& StorageItems);
	void SetStorageItem(int TabIdx, int SlotIdx, const FItemData& Item);
	
	void RequestGetStorageItems();
	void SendPktInventoryToStorage(const FItemData& Item, int Amount);
	void SendPktStorageToInventory(const FItemData& Item, int Amount);
	void SendPktGoods(bool bDeposit, int Amount);

};
