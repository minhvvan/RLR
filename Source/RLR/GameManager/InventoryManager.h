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
 DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateEquip, FItemData, NewEquipItem);
 DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateItemActionTag, FGameplayTag, ActionTag);
 DECLARE_DYNAMIC_DELEGATE_OneParam(FOnInventorySlotClicked, FItemData, SlotItemData);
 DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateEquip, FItemData, NewEquipItem, FItemResource, NewEquipItemResource);

UCLASS()
class RLR_API UInventoryManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection);


public:

	void Update();

	UFUNCTION(BlueprintCallable)
	void AddItem(const FItemData& NewItem);

	UFUNCTION(BlueprintCallable)
	void AddItemList(const TArray<FItemData>& NewItemList, const TArray<FItemResource>& NewItemResourceList);
	UFUNCTION(BlueprintCallable)
	void AddItemResourceList(const TArray<FItemResource>& NewItemResourceList);

	UFUNCTION(BlueprintCallable)
	FItemData GetItem(int32 ItemSeq);

	UFUNCTION(BlueprintCallable)
	void GetItemList(UPARAM(ref) TArray<FItemData>& ItemArray);

	UFUNCTION(BlueprintCallable)
	void SetItemList(TArray<FItemData>& ItemArray);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(int32 ItemSeq);
	bool EquipItem(int32 ItemSeq);								//아이템 장착
	bool UnEquipItem(int32 ItemSeq);
	void UsingItem(FGameplayTag TriggerTag);
	const FItemData* GetItemData(FGameplayTag TriggerTag);
	const FSkillDictionary<FGameplayTag, FItemData>& GetOwnItems();
	bool HasItemTag(FGameplayTag TriggerTag);

	UFUNCTION()
	void SetSelectedItems(TArray<FItemData>& SelectedItems);
	void GetItemList(UPARAM(ref) TArray<FItemData>& ItemArray);
	UFUNCTION(BlueprintCallable)
	void GetItemResourceList(UPARAM(ref) TArray<FItemResource>& ItemResourceArray);

  UFUNCTION(BlueprintCallable)
  const FItemResource GetItemResource(int32 ItemSeq) const;
  UFUNCTION(BlueprintCallable)
  bool TryGetItemResource(int32 ItemSeq, FItemResource& OutItemResource) const;

	UFUNCTION(BlueprintCallable)
	void ChangeItemSlot(int32 Item_Seq, int32 NewSlotIndex);	//슬롯 바꾸기.

	int32 GetCopper() {return Copper;}
	void SetCopper(int32 NewCopper);

	int32 GetSilver() {return Silver;}
	void SetSilver(int32 NewSilver);

	int32 GetGold(){return Gold;}
	void SetGold(int32 NewGold);

	int32 GetPlatinum() {return Platinum;}
	void SetPlatinum(int32 NewPlatinum);

//아이템 키값을 위한 임시용. 나중에 서버에서 아이템 패킷을 쏴주면 필요없어질 예정.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemKey = 0;

public:
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FUpdateInventoryManager OnUpdateInventoryDelegate;
	void OnUpdateInventoryDelegateBroadcast();

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FUpdateInventoryManager OnUpdateGoldAndCashDelegate;
	void OnUpdateGoldAndCashDelegateBroadcast();

	UPROPERTY()
	FUpdateEquip			OnUpdateEquipDelegate;
	void OnUpdateEquipDelegateBroadcast(FItemData EquipItem, FItemResource EquipItemResource);

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Copper;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Silver;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Gold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Platinum;

	//<DB Key , FItemData>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<int32, FItemData> ItemData;

	//아이템 퀵 슬롯
	FSkillDictionary<FGameplayTag, FItemData> OwnItems;

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

UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<int32, FItemResource> ItemResourceData;
};
