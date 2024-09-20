// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/InventoryManager.h"
#include "Structs/ItemStructs.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"


void UInventoryManager::Update()
{
	OnUpdateInventoryDelegateBroadcast();
	AsyncTask(ENamedThreads::GameThread, [this] {
	OnUpdateInventoryDelegate.Broadcast();
		});
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

void UInventoryManager::GetItemResourceList(UPARAM(ref)TArray<FItemResource>& ItemResourceArray)
{
	ItemResourceData.GenerateValueArray(ItemResourceArray);
}