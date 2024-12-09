// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager/DataManager.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "Structs/ItemStructs.h"
#include "InventoryManager.generated.h"

/**
	아이템 정보를 관리하는 매니저
 */

 DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateInventoryManager);
 DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateItemActionTag, FGameplayTag, ActionTag);
 DECLARE_DYNAMIC_DELEGATE_OneParam(FOnInventorySlotClicked, FItemData, SlotItemData);
 DECLARE_DYNAMIC_DELEGATE_OneParam(FOnInventorySlotShiftClicked, const FItemData&, SlotItemData);
 DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateEquip, FItemData, NewEquipItem);

UCLASS()
class RLR_API UInventoryManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection);


public:

	void Update();

	void AddItem(const FItemData& NewItem);
	void AddItemList(const TArray<FItemData>& NewItemList);

	FItemData GetItem(int32 Item_ID);
	void RemoveItem(int32 Item_ID);
	void RemoveItem(int32 Item_ID, int Amount);
	bool EquipItem(int32 Item_ID);								//아이템 장착
	bool UnEquipItem(int32 Item_ID);
	void UsingItem(FGameplayTag TriggerTag);
	const FItemData* GetItemData(FGameplayTag TriggerTag);
	const FSkillDictionary<FGameplayTag, FItemData>& GetOwnItems();
	bool HasItemTag(FGameplayTag TriggerTag);

	void SetSelectedItems(TArray<FItemData>& SelectedItems);
	void SetItemList(TArray<FItemData>& ItemArray);
	void GetItemList(UPARAM(ref) TArray<FItemData>& ItemArray);

	void ChangeItemSlot(int32 Item_ID, int32 NewSlotIndex);	//슬롯 바꾸기.

	int32 GetCopper() {return Copper;}
	void SetCopper(int32 NewCopper);

	int32 GetSilver() {return Silver;}
	void SetSilver(int32 NewSilver);

	int32 GetGold(){return Gold;}
	void SetGold(int32 NewGold);

	int32 GetPlatinum() {return Platinum;}
	void SetPlatinum(int32 NewPlatinum);

	UFUNCTION()
	void OnInventorySlotClicked(int32 SlotIndex, const FItemData& ItemData, ESlotType SlotType);

	UFUNCTION()
	void OnInventorySlotShiftClicked(int32 SlotIndex, const FItemData& ItemData, ESlotType SlotType);

	UFUNCTION()
	void OnInventorySlotAltClicked(int32 SlotIndex, const FItemData& ItemData, ESlotType SlotType);
	
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Copper;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Silver;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Gold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Platinum;

	//<DB Key , FItemData>		플레이어의 인벤토리 데이터
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<int32, FItemData> InventoryItemData;

	//<Input Key, FItemData>	아이템 퀵 슬롯
	FSkillDictionary<FGameplayTag, FItemData> ItemQuickSlots;

public:

	/*
		1.아이템 퀵 슬롯 위치 바뀌면 업데이트
	*/
	UPROPERTY()
	FUpdateInventoryManager UpdatedItemSettingDelegate;
	void UpdatedItemSettingBroadcast();

	UPROPERTY()
	FUpdateItemActionTag UpdatedTryUsingItemAction;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FUpdateInventoryManager OnUpdateInventoryDelegate;
	void OnUpdateInventoryDelegateBroadcast();

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FUpdateInventoryManager OnUpdateGoldAndCashDelegate;
	void OnUpdateGoldAndCashDelegateBroadcast();

	UPROPERTY()
	FUpdateEquip OnUpdateEquipDelegate;
	void OnUpdateEquipDelegateBroadcast(FItemData EquipItem);

	UPROPERTY()
	FOnInventorySlotClicked OnInventorySlotClickedDelegate;
	void OnInventorySlotClickedDelegateBroadcast(FItemData SlotItemData);

	UPROPERTY()
	FOnInventorySlotShiftClicked OnInventorySlotShiftClickedDelegate;
	void OnInventorySlotShiftClickedDelegateBroadcast(const FItemData& SlotItemData);
};
