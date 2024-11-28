// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StorageManager.generated.h"
#include "RLRStruct.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStorageAllItemUpdated, const TArray<TArray<FItemData>>&, Items);

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
	void SetStorageAllItems(const TArray<TArray<FItemData>>& StorageItems);
	void SendPktInventoryToStorage(const FItemData& Item, int Amount);
	void SendPktGoods(bool bDeposit, int Amount);
};
