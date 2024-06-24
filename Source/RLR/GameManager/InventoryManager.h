// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager/DataManager.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InventoryManager.generated.h"

/**
	아이템 정보를 관리하는 매니저
 */

 DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateInventoryManager);


UCLASS()
class RLR_API UInventoryManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void AddItem(FItemData NewItem);
	UFUNCTION(BlueprintCallable)
	FItemData GetItem(int32 Id);
	UFUNCTION(BlueprintCallable)
	void RemoveItem(int32 Id);

	UFUNCTION(BlueprintCallable)
	void GetItemList(UPARAM(ref) TArray<FItemData>& ItemArray);

	UFUNCTION(BlueprintCallable)
	int32 GetGold(){return Gold;}
	UFUNCTION(BlueprintCallable)
	void SetGold(int32 NewGold);

	UFUNCTION(BlueprintCallable)
	int32 GetCash() {return Cash;}
	UFUNCTION(BlueprintCallable)
	void SetCash(int32 NewCash);


//아이템 키값을 위한 임시용. 나중에 서버에서 아이템 패킷을 쏴주면 필요없어질 예정.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemKey = 0;

public:
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FUpdateInventoryManager OnUpdateInventoryManager;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FUpdateInventoryManager OnUpdateGoldAndCash;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Cash;

	//<DB Key , FItemData>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int32, FItemData> ItemData;
};
