// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/InventoryManager.h"
#include "Structs/ItemStructs.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"


void UInventoryManager::Update()
{
	OnUpdateInventoryDelegate.Broadcast();
}

void UInventoryManager::AddItem(FItemData NewItem)
{
	if (NewItem == FItemData::EmptyItemData)
	{
		DEBUG_LOG("Add Item Warning Message. NewItem is empty.");
		return;
	}
	

	ItemData.Add(NewItem.ITEM_SEQ, NewItem);
	OnUpdateInventoryDelegate.Broadcast();
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
		OnUpdateInventoryDelegate.Broadcast();
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
	OnUpdateEquipDelegate.Broadcast(EquipedItem);
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
	OnUpdateEquipDelegate.Broadcast(EquipedItem);
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
	OnUpdateGoldAndCashDelegate.Broadcast();
}

void UInventoryManager::SetPlatinum(int32 NewPlatinum)
{
	Platinum = NewPlatinum;
	OnUpdateGoldAndCashDelegate.Broadcast();
}

void UInventoryManager::SetCopper(int32 NewCopper)
{
	Copper = NewCopper;
	OnUpdateGoldAndCashDelegate.Broadcast();
}

void UInventoryManager::SetSilver(int32 NewSilver)
{
	Silver = NewSilver;
	OnUpdateGoldAndCashDelegate.Broadcast();
}

void UInventoryManager::GetItemList(TArray<FItemData>& ItemArray)
{
	ItemData.GenerateValueArray(ItemArray);
	/*AsyncTask(ENamedThreads::GameThread, [this] {
		Update();
		}
	);*/
	
}
