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
 DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateEquip, FItemData, NewEquipItem);


UCLASS()
class RLR_API UInventoryManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	void Update();

	UFUNCTION(BlueprintCallable)
	void AddItem(FItemData NewItem);
	UFUNCTION(BlueprintCallable)
	FItemData GetItem(int32 ItemSeq);
	UFUNCTION(BlueprintCallable)
	void RemoveItem(int32 ItemSeq);

	bool EquipItem(int32 ItemSeq);								//아이템 장착
	bool UnEquipItem(int32 ItemSeq);

	UFUNCTION(BlueprintCallable)
	void ChangeItemSlot(int32 Item_Seq, int32 NewSlotIndex);	//슬롯 바꾸기.

	UFUNCTION(BlueprintCallable)
	void GetItemList(UPARAM(ref) TArray<FItemData>& ItemArray);


	UFUNCTION(BlueprintCallable)
	int32 GetCopper() {return Copper;}

	UFUNCTION(BlueprintCallable)
	void SetCopper(int32 NewCopper);

	UFUNCTION(BlueprintCallable)
	int32 GetSilver() {return Silver;}
	UFUNCTION(BlueprintCallable)
	void SetSilver(int32 NewSilver);

	UFUNCTION(BlueprintCallable)
	int32 GetGold(){return Gold;}
	UFUNCTION(BlueprintCallable)
	void SetGold(int32 NewGold);

	UFUNCTION(BlueprintCallable)
	int32 GetPlatinum() {return Platinum;}

	UFUNCTION(BlueprintCallable)
	void SetPlatinum(int32 NewPlatinum);

//아이템 키값을 위한 임시용. 나중에 서버에서 아이템 패킷을 쏴주면 필요없어질 예정.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemKey = 0;

public:
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FUpdateInventoryManager OnUpdateInventoryDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FUpdateInventoryManager OnUpdateGoldAndCashDelegate;

	UPROPERTY()
	FUpdateEquip			OnUpdateEquipDelegate;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Copper;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Silver;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Gold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Platinum;


public:
	//<DB Key , FItemData>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<int32, FItemData> ItemData;
};
