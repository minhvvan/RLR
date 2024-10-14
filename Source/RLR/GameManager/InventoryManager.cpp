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
	OnUpdateGoldAndCashDelegate.Clear();
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
	
	ItemData.Add(NewItem.ITEM_SLOT_IDX, NewItem);
	OnUpdateInventoryDelegateBroadcast();
}

void UInventoryManager::AddItemList(const TArray<FItemData>& NewItemList, const TArray<FItemResource>& NewItemResourceList)
{
	for (const FItemData& NewItem : NewItemList)
	{
		if (NewItem == FItemData::EmptyItemData)
		{
			DEBUG_LOG("Add Item Warning Message. NewItem is empty.");
			return;
		}
		ItemData.Add(NewItem.ITEM_SLOT_IDX, NewItem);
	}

	AddItemResourceList(NewItemResourceList);

	OnUpdateInventoryDelegateBroadcast();
}

void UInventoryManager::AddItemResourceList(const TArray<FItemResource>& NewItemResourceList)
{
	for (const FItemResource& NewItemResource : NewItemResourceList)
	{
		if (NewItemResource.ITEM_SEQ == -1)
		{
			DEBUG_LOG("Add Item Resource Warning Message. NewItemResource is invalid.");
			continue;
		}
		ItemResourceData.Add(NewItemResource.ITEM_SEQ, NewItemResource);
	}
}


const FItemResource UInventoryManager::GetItemResource(int32 ItemSeq) const
{
	if (ItemResourceData.Contains(ItemSeq))
	{
		return ItemResourceData[ItemSeq];
	}
	return FItemResource::EmptyItemResource;
}

bool UInventoryManager::TryGetItemResource(int32 ItemSeq, FItemResource& OutItemResource) const
{
	if (ItemResourceData.Contains(ItemSeq))
	{
		OutItemResource = ItemResourceData[ItemSeq];
		return true;
	}
	OutItemResource = FItemResource::EmptyItemResource;
	return false;
}

FItemData UInventoryManager::GetItem(int32 Id)
{
	if (ItemData.Contains(Id))
	{
		return ItemData[Id];
	}
	return FItemData::EmptyItemData;
}

void UInventoryManager::GetItemList(TArray<FItemData>& ItemArray)
{
	ItemData.GenerateValueArray(ItemArray);
}
void UInventoryManager::SetItemList(TArray<FItemData>& ItemArray) {
	ItemData.Empty();

	for (const FItemData& Item : ItemArray)
	{
		ItemData.Add(Item.ITEM_SEQ, Item);
	}

	Update();

}

void UInventoryManager::RemoveItem(int32 Id)
{
	if (ItemData.Contains(Id))
	{
		FItemData RemoveItem;
		ItemData.RemoveAndCopyValue(Id, RemoveItem);
		OnUpdateInventoryDelegateBroadcast();
	}
}

bool UInventoryManager::EquipItem(int32 ItemSeq)
{
	if (ItemData.Contains(ItemSeq) == false)
	{
		DEBUG_LOG("EquipItem Error. ItemData is Null");
		return false;
	}

	FItemData& EquipedItem = ItemData[ItemSeq];
	FItemResource& EquipedItemResource = ItemResourceData[ItemSeq];
	EquipedItem.IsEquiped = true;
	OnUpdateEquipDelegateBroadcast(EquipedItem, EquipedItemResource);
	return true;
}

bool UInventoryManager::UnEquipItem(int32 ItemSeq)
{
	if (ItemData.Contains(ItemSeq) == false)
	{
		DEBUG_LOG("EquipItem Error. ItemData is Null");
		return false;
	}

	FItemData& EquipedItem = ItemData[ItemSeq];
	FItemResource& EquipedItemResource = ItemResourceData[ItemSeq];
	EquipedItem.IsEquiped = false;
	OnUpdateEquipDelegateBroadcast(EquipedItem, EquipedItemResource);
	return true;
}

void UInventoryManager::ChangeItemSlot(int32 Item_Seq, int32 NewSlotIndex)
{
	if (ItemData.Contains(Item_Seq))
	{
		ItemData[Item_Seq].ITEM_SLOT_IDX = NewSlotIndex;
	}
}

void UInventoryManager::SetGold(int32 NewGold)
{
	Gold = NewGold;
	OnUpdateGoldAndCashDelegateBroadcast();
}

void UInventoryManager::SetPlatinum(int32 NewPlatinum)
{
	Platinum = NewPlatinum;
	OnUpdateGoldAndCashDelegateBroadcast();
}

void UInventoryManager::SetCopper(int32 NewCopper)
{
	Copper = NewCopper;
	OnUpdateGoldAndCashDelegateBroadcast();
}

void UInventoryManager::SetSilver(int32 NewSilver)
{
	Silver = NewSilver;
	OnUpdateGoldAndCashDelegateBroadcast();
}

void UInventoryManager::UsingItem(FGameplayTag TriggerTag)
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

const FItemData* UInventoryManager::GetItemData(FGameplayTag TriggerTag)
{
	for (auto& [Tag, Data] : OwnItems)
	{
		if (TriggerTag.MatchesTag(Tag))
		{
			return &Data;
		}
	}
	return nullptr;
}

const FSkillDictionary<FGameplayTag, FItemData>& UInventoryManager::GetOwnItems()
{
	return OwnItems;
}

bool UInventoryManager::HasItemTag(FGameplayTag TriggerTag)
{
	bool bResult = false;
	for (auto& [Tag, Data] : OwnItems)
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
	OwnItems.Empty();

	for (int i = 0; i < SelectedItems.Num(); i++)
	{
		const FItemData& Data = SelectedItems[i];
		if (Data == FItemData::EmptyItemData)
		{
			RLR_LOG(LogRLR, Log, TEXT("Not Found Skill Class"));
			return;
		}

		//아이템 태는 퀵 슬롯 인덱스 번호로 맞춰야 함  -> ItemQuickSlot.{퀵 슬롯 인덱스 번호}
		FGameplayTag ItemTag = ItemTags->GetByIndex(Data.ITEM_SLOT_IDX);
		OwnItems.Add(ItemTag, SelectedItems[i]);
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

void UInventoryManager::OnUpdateGoldAndCashDelegateBroadcast()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			// 유효성 검사 추가
			if (!IsValid(this))
			{
				DEBUG_MESSAGE;
				return;
			}
			OnUpdateGoldAndCashDelegate.Broadcast();
		});
}

void UInventoryManager::OnUpdateEquipDelegateBroadcast(FItemData EquipItem, FItemResource EquipItemResource)
{
	AsyncTask(ENamedThreads::GameThread, [this, EquipItem, EquipItemResource]()
		{
			// 유효성 검사 추가
			if (!IsValid(this))
			{
				DEBUG_MESSAGE;
				return;
			}
			OnUpdateEquipDelegate.Broadcast(EquipItem, EquipItemResource);
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
void UInventoryManager::SetItemList(TArray<FItemData>& ItemArray) 
{
	ItemData.Empty();

	for (const FItemData& Item : ItemArray)
	{
		ItemData.Add(Item.ITEM_SEQ, Item);
	}
	
	Update();
	
}

void UInventoryManager::GetItemResourceList(UPARAM(ref)TArray<FItemResource>& ItemResourceArray)
{
	ItemResourceData.GenerateValueArray(ItemResourceArray);
}
