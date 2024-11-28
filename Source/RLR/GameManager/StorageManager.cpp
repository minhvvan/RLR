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

void UStorageManager::RequestGetStorageItems()
{
	//TODO: Send Pkt Get Storage Items

	//test==========================================
	TArray<TArray<FItemData>> items;
	const int MaxStoragePageNum = 5;
	const int MaxStorageSlotNum = 50;
	items.SetNum(MaxStoragePageNum);
	for (int i = 0; i < MaxStoragePageNum; i++)
	{
		items[i].SetNum(MaxStorageSlotNum);
	}
	SetStorageAllItems(items);
	//==========================================
}

void UStorageManager::SetStorageAllItems(const TArray<TArray<FItemData>>& StorageItems)
{
	Items = StorageItems;
	OnStorageAllItemUpdated.Broadcast();
}

void UStorageManager::SetStorageItem(int TabIdx, int SlotIdx, const FItemData& Item)
{
	auto StorageUI = GameInstance->GetUIManager()->GetSubUI<UStorageUI>(RLRTAG.UI_Storage);
	if (!StorageUI) RLR_LOG_END(LogRLR, Log, TEXT("StorageUI is nullptr"));

	FItemData data = Item.QUANTITY == 0 ? FItemData::EmptyItemData : Item;
	StorageUI->SetSlotItem(TabIdx, SlotIdx, data);
}

void UStorageManager::SendPktInventoryToStorage(const FItemData& Item, int Amount)
{
	//TODO: pkt 전송(itemID? seq?, count)
	//NetworkManager->SendPkt
	//callback에서는 inventory 개수만큼 제외 + storage에 추가(SetSlotItem사용)
	
	//Test
	//==========================================================================
	GameInstance->GetInventoryManager()->RemoveItem(Item.ITEM_ID, Amount);

	auto tempItem(Item);
	tempItem.QUANTITY = Amount;
	SetStorageItem(0, tempItem.ITEM_SLOT_IDX, tempItem);

	RLR_LOG(LogRLR, Log, TEXT("Item: %d, %d"), Item.ITEM_ID, Item.QUANTITY);
	//==========================================================================
}

void UStorageManager::SendPktStorageToInventory(const FItemData& Item, int Amount)
{
	//TODO: 창고 -> 인벤토리 패킷 전송(pageIdx, slot_idx?(item_id?))
	//callback에서는 inventory 개수만큼 추가 + storage에서 제거(SetSlotItem사용)

	//Test
	//==========================================================================
	{
		FItemData tempItem(Item);
		tempItem.QUANTITY = Amount;
		GameInstance->GetInventoryManager()->AddItem(tempItem);
	}

	{
		FItemData tempItem(Item);
		tempItem.QUANTITY -= Amount;
		SetStorageItem(0, tempItem.ITEM_SLOT_IDX, tempItem);
	}

	RLR_LOG(LogRLR, Log, TEXT("Item: %d, %d"), Item.ITEM_ID, Item.QUANTITY);
	//==========================================================================
}

void UStorageManager::SendPktGoods(bool bDeposit, int Amount)
{
	//Callback에서 SetBalance 사용
	if (bDeposit)
	{
		//TODO: 인벤 -> 창고 pkt 전송
	}
	else
	{
		//TODO: 창고 -> 인벤 pkt 전송
	}
}
