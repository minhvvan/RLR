// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/InventoryManager.h"
#include "Structs/ItemStructs.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"


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

void UInventoryManager::AddItemList(const TArray<FItemData>& NewItemList)
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
	OnUpdateInventoryDelegateBroadcast();
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
	EquipedItem.IsEquiped = true;
	OnUpdateEquipDelegateBroadcast(EquipedItem);
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
	EquipedItem.IsEquiped = false;
	OnUpdateEquipDelegateBroadcast(EquipedItem);
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
