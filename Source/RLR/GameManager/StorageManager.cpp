// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/StorageManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/UIManager.h"
#include "Structs/ItemStructs.h"
#include "UI/InGame/Storage/StorageUI.h"
#include "RLR.h"

const TArray<TArray<FItemData>>& UStorageManager::GetAllItems()
{
	return Items;
}

const TArray<FItemData>& UStorageManager::GetItemPage(int page)
{
	if (MaxStoragePageNum < page)
	{
		RLR_LOG(LogRLR, Log, TEXT("page is exceeded MaxStoragePageNum"));
	}
	
	return Items[page];
}

void UStorageManager::SetStorageAllItems(const TArray<TArray<FItemData>>& StorageItems)
{
	Items = StorageItems;
	OnStorageAllItemUpdated.Broadcast();
}

void UStorageManager::SetStorageItemPage(int PageIndex,const TArray<FItemData>& StorageItems)
{
	if (Items.Num() != MaxStoragePageNum)
	{
		Items.SetNum(MaxStoragePageNum);
	}

	Items[PageIndex] = StorageItems;
	OnStoragePageItemUpdated.Broadcast(PageIndex);
}

void UStorageManager::SetStorageItem(int PageIndex, int SlotIdx, const FItemData& Item)
{
	auto StorageUI = GameInstance->GetUIManager()->GetSubUI<UStorageUI>(RLRTAG.UI_Storage);
	if (!StorageUI)
	{
		RLR_LOG(LogRLR, Log, TEXT("StorageUI is nullptr"));
		return;
	}
	
	FItemData data = Item.QUANTITY == 0 ? FItemData::EmptyItemData : Item;
	Items[PageIndex][SlotIdx] = Item;

	StorageUI->SetSlotItem(PageIndex, SlotIdx, data);
}

void UStorageManager::RequestGetStorageItems()
{
	//TODO: Send Pkt Get Storage Items

	//test==========================================
	TArray<TArray<FItemData>> items;
	items.SetNum(MaxStoragePageNum);
	for (int i = 0; i < MaxStoragePageNum; i++)
	{
		items[i].SetNum(MaxStorageSlotNum);
		for (int j = 0; j < MaxStorageSlotNum; j++)
		{
			items[i][j].ITEM_SLOT_IDX = i * MaxStoragePageNum + j;
		}
		
		SetStorageItemPage(i, items[i]);
	}
	
	//==========================================
}

void UStorageManager::SwapItems(int TabIdx, int lhsSlotIndex, const FItemData& lhs, int rhsSlotIndex, const FItemData& rhs)
{
	//TODO: SendPkt Swap
	SetStorageItem(TabIdx, rhsSlotIndex, lhs);
	SetStorageItem(TabIdx, lhsSlotIndex, rhs);
}

void UStorageManager::SendPktMoveItemInventoryToStorage(const FItemData& Item, int Amount, int PageIndex, int SlotIndex)
{
	//TODO: SendPkt ItemMove(Inventory -> Storage)

	//TODO at Response
	/*====================================================================
	GameInstance->GetInventoryManager()->RemoveItem(Item.ITEM_ID, Amount);
	SetStorageItem(PageIndex, SlotIndex, newItem);
	====================================================================*/

	//Test=============================================================
	{
		GameInstance->GetInventoryManager()->RemoveItem(Item.ITEM_ID, Amount);

		if (SlotIndex == -1)
		{
			for (int i = 0; i < MaxStorageSlotNum; i++)
			{
				if (Items[PageIndex][i] == FItemData::EmptyItemData)
				{
					SlotIndex = i;
					break;
				}
			}
		}
	
		auto newItem(Item);
		newItem.QUANTITY = Amount;
		SetStorageItem(PageIndex, SlotIndex, newItem);
	}
	//=================================================================
}

void UStorageManager::SendPktMoveItemStorageToInventory(const FItemData& Item, int Amount, int PageIndex, int SlotIndex)
{
	//TODO: SendPkt ItemMove(Storage -> Inventory)

	//TODO at Response
	/*====================================================================
	GameInstance->GetInventoryManager()->AddItem(newItem);
	SetStorageItem(PageIndex, SlotIndex, oldItem(만약 empty => FItemData::EmptyItemData));
	====================================================================*/

	//Test=============================================================
	{
		FItemData tempItem(Item);
		tempItem.QUANTITY = Amount;
		GameInstance->GetInventoryManager()->AddItem(tempItem);
	}

	{
		FItemData tempItem(Item);
		tempItem.QUANTITY -= Amount;
		if (tempItem.QUANTITY == 0) tempItem = FItemData::EmptyItemData;
		
		SetStorageItem(PageIndex, SlotIndex, tempItem);
		Items[PageIndex][SlotIndex] = tempItem;
	}
	//=================================================================
}