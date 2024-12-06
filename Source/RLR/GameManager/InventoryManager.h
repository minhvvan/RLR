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
	FItemData GetItemBySlotIndex(int32 InventoryIdx);
	void RemoveItem(int32 Item_ID);
	bool EquipItem(int32 Item_ID);								//아이템 장착
	bool UnEquipItem(int32 Item_ID);
	void UsingQuickSlotItem(FGameplayTag TriggerTag);
	const FItemData* GetQuickSlotItemData(FGameplayTag TriggerTag);
	const FSkillDictionary<FGameplayTag, FItemData>& GetItemQuickSlots();
	bool HasItemTag(FGameplayTag TriggerTag);

	void SetSelectedItems(TArray<FItemData>& SelectedItems);
	void SetItemList(TArray<FItemData>& ItemArray);
	void GetItemList(UPARAM(ref) TArray<FItemData>& ItemArray);

	void ChangeItemSlot(int32 Item_ID, int32 NewSlotIndex);	//슬롯 바꾸기.

private:

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

	UPROPERTY()
	FUpdateEquip OnUpdateEquipDelegate;
	void OnUpdateEquipDelegateBroadcast(FItemData EquipItem);

	UPROPERTY()
	FOnInventorySlotClicked OnInventorySlotClickedDelegate;
	void OnInventorySlotClickedDelegateBroadcast(FItemData SlotItemData);
};
