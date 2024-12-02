// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/InventoryManager.h"
#include "GameManager/GameplayTagManager.h"

#include "Structs/ItemStructs.h"

#include "Player/RLRPlayerController.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>


void UInventoryManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UpdatedItemSettingDelegate.Clear();
	UpdatedTryUsingItemAction.Clear();
	OnUpdateInventoryDelegate.Clear();
	OnUpdateEquipDelegate.Clear();
}

void UInventoryManager::Update()
{
	OnUpdateInventoryDelegateBroadcast();
}

void UInventoryManager::AddItem(const FItemData& NewItem)
{
	if (NewItem == FItemData::EmptyItemData)
	{
		DEBUG_LOG("Add Item Warning Message. NewItem is empty.");
		return;
	}
	
	InventoryItemData.Add(NewItem.ITEM_ID, NewItem);
	OnUpdateInventoryDelegateBroadcast();
}

void UInventoryManager::AddItemList(const TArray<FItemData>& NewItemList)
{
	for (const FItemData& NewItem : NewItemList)
	{
		if (NewItem == FItemData::EmptyItemData)
		{
			DEBUG_LOG("Add Item Warning Message. NewItem is empty.");
			return;
		}
		InventoryItemData.Add(NewItem.ITEM_ID, NewItem);
	}
	OnUpdateInventoryDelegateBroadcast();
}

FItemData UInventoryManager::GetItem(int32 Item_ID)
{
	if (InventoryItemData.Contains(Item_ID))
	{
		return InventoryItemData[Item_ID];
	}
	return FItemData::EmptyItemData;
}

void UInventoryManager::GetItemList(TArray<FItemData>& ItemArray)
{
	InventoryItemData.GenerateValueArray(ItemArray);
}
void UInventoryManager::SetItemList(TArray<FItemData>& ItemArray) {
	InventoryItemData.Empty();

	for (const FItemData& Item : ItemArray)
	{
		InventoryItemData.Add(Item.ITEM_ID, Item);
	}

	Update();
}

void UInventoryManager::RemoveItem(int32 Item_ID)
{
	if (InventoryItemData.Contains(Item_ID) == true)
	{
		FItemData RemoveItem;
		InventoryItemData.RemoveAndCopyValue(Item_ID, RemoveItem);
		OnUpdateInventoryDelegateBroadcast();
	}
}

bool UInventoryManager::EquipItem(int32 Item_ID)
{
	if (InventoryItemData.Contains(Item_ID) == false)
	{
		DEBUG_LOG("EquipItem Error. ItemData is Null");
		return false;
	}

	FItemData& EquipedItem = InventoryItemData[Item_ID];
	EquipedItem.IsEquiped = true;
	OnUpdateEquipDelegateBroadcast(EquipedItem);
	return true;
}

bool UInventoryManager::UnEquipItem(int32 Item_ID)
{
	if (InventoryItemData.Contains(Item_ID) == false)
	{
		DEBUG_LOG("EquipItem Error. ItemData is Null");
		return false;
	}

	FItemData& EquipedItem = InventoryItemData[Item_ID];
	EquipedItem.IsEquiped = false;
	OnUpdateEquipDelegateBroadcast(EquipedItem);
	return true;
}

void UInventoryManager::ChangeItemSlot(int32 Item_ID, int32 NewSlotIndex)
{
	if (InventoryItemData.Contains(Item_ID))
	{
		InventoryItemData[Item_ID].ITEM_SLOT_IDX = NewSlotIndex;
	}
}

void UInventoryManager::UsingQuickSlotItem(FGameplayTag TriggerTag)
{
	if (HasItemTag(TriggerTag) == false)
		return;

	{
		//TODO. 서버에 아이템 사용 패킷을 보낸다.
		//이 부분은 여기서 바로 패킷을 보낼 건지, ActionComponent에서 처리할 건지 민환님이랑 이야기해볼 것.
		//const FItemData* ItemData = GetItemData(TriggerTag);
		//GameInstance->GetNetworkManager()->SendUsingItemPacket(*ItemData);
	}

	UpdatedTryUsingItemAction.Broadcast(TriggerTag);
}

const FItemData* UInventoryManager::GetQuickSlotItemData(FGameplayTag TriggerTag)
{
	for (auto& [Tag, Data] : ItemQuickSlots)
	{
		if (TriggerTag.MatchesTag(Tag))
		{
			return &Data;
		}
	}
	return nullptr;
}

const FSkillDictionary<FGameplayTag, FItemData>& UInventoryManager::GetItemQuickSlots()
{
	return ItemQuickSlots;
}

bool UInventoryManager::HasItemTag(FGameplayTag TriggerTag)
{
	bool bResult = false;
	for (auto& [Tag, Data] : ItemQuickSlots)
	{
		if (TriggerTag.MatchesTag(Tag))
		{
			bResult = true;
			break;
		}
	}

	return bResult;
}

void UInventoryManager::SetSelectedItems(TArray<FItemData>& SelectedItems)
{
	// GameplayTagManager
	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	const FGameplayTagContainer* ItemTags = TagManager.GetItemTags();
	ItemQuickSlots.Empty();

	for (int i = 0; i < SelectedItems.Num(); i++)
	{
		const FItemData& Data = SelectedItems[i];
		if (Data == FItemData::EmptyItemData)
		{
			RLR_LOG(LogRLR, Log, TEXT("Not Found Skill Class"));
			return;
		}

		//아이템 태그는 퀵 슬롯 인덱스 번호로 맞춰야 함  -> ItemQuickSlot.{퀵 슬롯 인덱스 번호}
		FGameplayTag ItemTag = ItemTags->GetByIndex(Data.ITEM_SLOT_IDX);
		ItemQuickSlots.Add(ItemTag, SelectedItems[i]);
	}

	UpdatedItemSettingBroadcast();
}

void UInventoryManager::UpdatedItemSettingBroadcast()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			// 유효성 검사 추가
			if (!IsValid(this))
			{
				RLR_LOG(LogRLR, Warning, TEXT("SkillManager is invalid during broadcast."));
				return;
			}
			UpdatedItemSettingDelegate.Broadcast();
		});
}

void UInventoryManager::OnUpdateInventoryDelegateBroadcast()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			// 유효성 검사 추가
			if (!IsValid(this))
			{
				DEBUG_MESSAGE;
				return;
			}
			OnUpdateInventoryDelegate.Broadcast();
		});
}

void UInventoryManager::OnUpdateEquipDelegateBroadcast(FItemData EquipItem)
{
	AsyncTask(ENamedThreads::GameThread, [this, EquipItem]()
		{
			// 유효성 검사 추가
			if (!IsValid(this))
			{
				DEBUG_MESSAGE;
				return;
			}
			OnUpdateEquipDelegate.Broadcast(EquipItem);
		});
}

void UInventoryManager::OnInventorySlotClickedDelegateBroadcast(FItemData SlotItemData)
{
	AsyncTask(ENamedThreads::GameThread, [this, SlotItemData]()
		{
			// 유효성 검사 추가
			if (!IsValid(this))
			{
				DEBUG_MESSAGE;
				return;
			}
			OnInventorySlotClickedDelegate.ExecuteIfBound(SlotItemData);
		});
}