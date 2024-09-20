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
	void AddItemList(const TArray<FItemData>& NewItemList);

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
	FUpdateInventoryManager UpdatedItemSettingDelegate;
	void UpdatedItemSettingBroadcast();

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
};
