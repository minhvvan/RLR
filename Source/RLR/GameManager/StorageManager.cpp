// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/StorageManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/UIManager.h"
#include "Structs/ItemStructs.h"
#include "Structs/UtilStructs.h"
#include "UI/InGame/Storage/StorageUI.h"
#include "RLR.h"
#include "UI/SlotUI.h"

const TArray<TArray<FItemData>>& UStorageManager::GetUserStorageItems()
{
	return UserStorageItems;
}

const TArray<FItemData>& UStorageManager::GetUserStorageItemPage(int page)
{
	if (MaxStoragePageNum < page)
	{
		RLR_LOG(LogRLR, Log, TEXT("page is exceeded MaxStoragePageNum"));
	}
	
	return UserStorageItems[page];
}

void UStorageManager::SetUserStorageAllItems(const TArray<TArray<FItemData>>& StorageItems)
{
	UserStorageItems = StorageItems;
	OnUserStorageAllItemUpdated.Broadcast();
}

void UStorageManager::SetUserStorageItemPage(int PageIndex,const TArray<FItemData>& StorageItems)
{
	if (UserStorageItems.Num() != MaxStoragePageNum)
	{
		UserStorageItems.SetNum(MaxStoragePageNum);
	}

	UserStorageItems[PageIndex] = StorageItems;
	OnUserStoragePageItemUpdated.Broadcast(PageIndex);
}

void UStorageManager::SetUserStorageItem(int PageIndex, int SlotIdx, const FItemData& Item)
{
	auto UserStorageUI = GameInstance->GetUIManager()->GetSubUI<UStorageUI>(RLRTAG.UI_Storage_User);
	if (!UserStorageUI)
	{
		RLR_LOG(LogRLR, Log, TEXT("UserStorageUI is nullptr"));
		return;
	}
	
	FItemData data = Item.ITEM_QUANTITY == 0 ? FItemData::EmptyItemData : Item;
	UserStorageItems[PageIndex][SlotIdx] = Item;

	UserStorageUI->SetSlotItem(PageIndex, SlotIdx, data);
}

void UStorageManager::SetPlayerStorageAllItems(const TArray<TArray<FItemData>>& StorageItems)
{
	PlayerStorageItems = StorageItems;
	OnPlayerStorageAllItemUpdated.Broadcast();
}

void UStorageManager::SetPlayerStorageItemPage(int PageIndex, const TArray<FItemData>& StorageItems)
{
	if (PlayerStorageItems.Num() != MaxStoragePageNum)
	{
		PlayerStorageItems.SetNum(MaxStoragePageNum);
	}

	PlayerStorageItems[PageIndex] = StorageItems;
	OnPlayerStoragePageItemUpdated.Broadcast(PageIndex);
}

void UStorageManager::SetPlayerStorageItem(int PageIndex, int SlotIdx, const FItemData& Item)
{
	auto PlayerStorageUI = GameInstance->GetUIManager()->GetSubUI<UStorageUI>(RLRTAG.UI_Storage_Player);
	if (!PlayerStorageUI)
	{
		RLR_LOG(LogRLR, Log, TEXT("PlayerStorageUI is nullptr"));
		return;
	}
	
	FItemData data = Item.ITEM_QUANTITY == 0 ? FItemData::EmptyItemData : Item;
	PlayerStorageItems[PageIndex][SlotIdx] = Item;

	PlayerStorageUI->SetSlotItem(PageIndex, SlotIdx, data);
}

void UStorageManager::RequestGetUserStorageItems()
{
	//TODO: Send Pkt Get Storage Items

	//test==========================================
	TArray<TArray<FItemData>> items;
	items.SetNum(MaxStoragePageNum);
	for (int i = 0; i < MaxStoragePageNum; i++)
	{
		items[i].SetNum(MaxStorageSlotNum);
		SetUserStorageItemPage(i, items[i]);
	}
	
	//==========================================
}

void UStorageManager::RequestGetPlayerStorageItems()
{
	//TODO: Send Pkt Get Storage Items

	//test==========================================
	TArray<TArray<FItemData>> items;
	items.SetNum(MaxStoragePageNum);
	for (int i = 0; i < MaxStoragePageNum; i++)
	{
		items[i].SetNum(MaxStorageSlotNum);
		SetPlayerStorageItemPage(i, items[i]);
	}
	//==========================================
}

void UStorageManager::SwapStorageItems(int PageIndex, int lhsSlotIndex, const FItemData& lhs, int rhsSlotIndex,
	const FItemData& rhs, ESlotType SlotType)
{
	if (SlotType == ESlotType::PLAYER_STORAGE_ITEM_SLOT)
	{
		//TODO: Send PlayerStorage Swap

		//TODO at Response
		/*===============================================
		SetPlayerStorageItem(PageIndex, rhsSlotIndex, lhs);
		SetPlayerStorageItem(PageIndex, lhsSlotIndex, rhs);
		================================================*/

		auto tempItem = rhs;
		SetPlayerStorageItem(PageIndex, rhsSlotIndex, lhs);
		SetPlayerStorageItem(PageIndex, lhsSlotIndex, tempItem);
	}
	else if (SlotType == ESlotType::USER_STORAGE_ITEM_SLOT)
	{
		//TODO: Send UserStorage Swap
		
		//TODO at Response
		/*===============================================
		SetUserStorageItem(PageIndex, rhsSlotIndex, lhs);
		SetUserStorageItem(PageIndex, lhsSlotIndex, rhs);
		================================================*/
		
		//Test
		auto tempItem = rhs;
		SetUserStorageItem(PageIndex, rhsSlotIndex, lhs);
		SetUserStorageItem(PageIndex, lhsSlotIndex, tempItem);
	}
}

void UStorageManager::SendPktMoveItemInventoryToUserStorage(const FItemData& Item, int Amount, int StorageSLotIndex, int InventorySlotIndex)
{
	//TODO: SendPkt ItemMove(Inventory -> UserStorage)

	//TODO at Response
	/*====================================================================
	GameInstance->GetInventoryManager()->RemoveItem(Item.ITEM_ID, Amount);
	SetUserStorageItem(PageIndex, StorageSLotIndex, newItem);
	====================================================================*/

	//Test=============================================================
	{
		auto storageUI = GameInstance->GetUIManager()->GetSubUI<UStorageUI>(RLRTAG.UI_Storage_User);
		if (!storageUI)
		{
			RLR_LOG(LogRLR, Log, TEXT("storageUI is nullptr"));
			return;
		}
		
		GameInstance->GetInventoryManager()->RemoveItem(Item.ITEM_ID, Amount);
		int PageIndex = storageUI->GetCurrentPage();
		
		if (StorageSLotIndex == -1)
		{
			for (int i = 0; i < MaxStorageSlotNum; i++)
			{
				if (UserStorageItems[PageIndex][i] == FItemData::EmptyItemData)
				{
					StorageSLotIndex = i;
					break;
				}
			}
		}
	
		auto newItem(Item);
		newItem.ITEM_QUANTITY = Amount;
		SetUserStorageItem(PageIndex, StorageSLotIndex, newItem);
	}
	//=================================================================
}

void UStorageManager::SendPktMoveItemUserStorageToInventory(const FItemData& Item, int Amount, int StorageSLotIndex, int InventorySlotIndex)
{
	//TODO: SendPkt ItemMove(UserStorage -> Inventory)

	//TODO at Response
	/*====================================================================
	GameInstance->GetInventoryManager()->AddItem(newItem, InventorySlotIndex);
	SetUserStorageItem(PageIndex, SlotIndex, oldItem(만약 empty => FItemData::EmptyItemData));
	====================================================================*/

	//Test=============================================================
	{
		FItemData tempItem(Item);
		tempItem.ITEM_QUANTITY = Amount;
		//TODO: Inventory.SlotIndex를 Item으로 변경
		GameInstance->GetInventoryManager()->AddItem(tempItem, InventorySlotIndex);
	}

	auto userStorageUI = GameInstance->GetUIManager()->GetSubUI<UStorageUI>(RLRTAG.UI_Storage_User);
	if (!userStorageUI)
	{
		RLR_LOG(LogRLR, Log, TEXT("UserStorageUI is nullptr"));
		return;
	}

	{
		int32 PageIndex = userStorageUI->GetCurrentPage();
		FItemData tempItem(Item);
		tempItem.ITEM_QUANTITY -= Amount;
		if (tempItem.ITEM_QUANTITY == 0) tempItem = FItemData::EmptyItemData;
		
		SetUserStorageItem(PageIndex, StorageSLotIndex, tempItem);
	}
	//=================================================================
}

void UStorageManager::SendPktMoveItemInventoryToStorage(const FItemData& Item, int Amount, ESlotType SlotType, int StorageSLotIndex, int InventorySlotIndex)
{
	if (SlotType == ESlotType::USER_STORAGE_ITEM_SLOT)
	{
		SendPktMoveItemInventoryToUserStorage(Item, Amount, StorageSLotIndex, InventorySlotIndex);
	}
	else if (SlotType == ESlotType::PLAYER_STORAGE_ITEM_SLOT)
	{
		SendPktMoveItemInventoryToPlayerStorage(Item, Amount, StorageSLotIndex, InventorySlotIndex);
	}
}

void UStorageManager::SendPktMoveItemStorageToInventory(const FItemData& Item, int Amount, ESlotType SlotType, int StorageSLotIndex, int InventorySlotIndex)
{
	if (SlotType == ESlotType::USER_STORAGE_ITEM_SLOT)
	{
		SendPktMoveItemUserStorageToInventory(Item, Amount, StorageSLotIndex, InventorySlotIndex);
	}
	else if (SlotType == ESlotType::PLAYER_STORAGE_ITEM_SLOT)
	{
		SendPktMoveItemPlayerStorageToInventory(Item, Amount, StorageSLotIndex, InventorySlotIndex);
	}
}

void UStorageManager::SendPktMoveItemInventoryToPlayerStorage(const FItemData& Item, int Amount, int StorageSLotIndex, int InventorySlotIndex)
{
	//TODO: SendPkt ItemMove(Inventory -> PlayerStorage)

	//TODO at Response
	/*====================================================================
	GameInstance->GetInventoryManager()->RemoveItem(Item.ITEM_ID, Amount);
	SetPlayerStorageItem(PageIndex, SlotIndex, newItem);
	====================================================================*/

	//Test=============================================================
	{
		auto playerStorageUI = GameInstance->GetUIManager()->GetSubUI<UStorageUI>(RLRTAG.UI_Storage_Player);
		if (!playerStorageUI)
		{
			RLR_LOG(LogRLR, Log, TEXT("playerStorageUI is nullptr"));
			return;
		}
		
		GameInstance->GetInventoryManager()->RemoveItem(Item.ITEM_ID, Amount);
		int PageIndex = playerStorageUI->GetCurrentPage();
		
		if (StorageSLotIndex == -1)
		{
			for (int i = 0; i < MaxStorageSlotNum; i++)
			{
				if (PlayerStorageItems[PageIndex][i] == FItemData::EmptyItemData)
				{
					StorageSLotIndex = i;
					break;
				}
			}
		}
	
		auto newItem(Item);
		newItem.ITEM_QUANTITY = Amount;
		SetPlayerStorageItem(PageIndex, StorageSLotIndex, newItem);
	}
	//=================================================================
}

void UStorageManager::SendPktMoveItemPlayerStorageToInventory(const FItemData& Item, int Amount, int StorageSLotIndex, int InventorySlotIndex)
{
	//TODO: SendPkt ItemMove(PlayerStorage -> Inventory)

	//TODO at Response
	/*====================================================================
	GameInstance->GetInventoryManager()->AddItem(newItem);
	SetPlayerStorageItem(PageIndex, SlotIndex, oldItem(만약 empty => FItemData::EmptyItemData));
	====================================================================*/

	//Test=============================================================
	{
		FItemData tempItem(Item);
		tempItem.ITEM_QUANTITY = Amount;
		GameInstance->GetInventoryManager()->AddItem(tempItem, InventorySlotIndex);
	}

	auto playerStorageUI = GameInstance->GetUIManager()->GetSubUI<UStorageUI>(RLRTAG.UI_Storage_Player);
	if (!playerStorageUI)
	{
		RLR_LOG(LogRLR, Log, TEXT("playerStorageUI is nullptr"));
		return;
	}

	{
		int32 PageIndex = playerStorageUI->GetCurrentPage();
		FItemData tempItem(Item);
		tempItem.ITEM_QUANTITY -= Amount;
		if (tempItem.ITEM_QUANTITY == 0) tempItem = FItemData::EmptyItemData;
		
		SetPlayerStorageItem(PageIndex, StorageSLotIndex, tempItem);
		PlayerStorageItems[PageIndex][StorageSLotIndex] = tempItem;
	}
	//=================================================================
}


void UStorageManager::SendPktSwapStorageItem(const FItemData& PlayerStorageItem, const FItemData& UserStorageItem, int PlayerStorageIndex, int UserStorageIndex)
{
	//TODO: SendPkt ItemSwap(PlayerStorage <-> UserStorage)
	auto playerStorageUI = GameInstance->GetUIManager()->GetSubUI<UStorageUI>(RLRTAG.UI_Storage_Player);
	if (!playerStorageUI)
	{
		RLR_LOG(LogRLR, Log, TEXT("playerStorageUI is nullptr"));
		return;
	}

	auto UserStorageUI = GameInstance->GetUIManager()->GetSubUI<UStorageUI>(RLRTAG.UI_Storage_User);
	if (!UserStorageUI)
	{
		RLR_LOG(LogRLR, Log, TEXT("UserStorageUI is nullptr"));
		return;
	}

	auto tempItem = UserStorageItem;
	SetUserStorageItem(UserStorageUI->GetCurrentPage(), UserStorageIndex, PlayerStorageItem);
	SetPlayerStorageItem(playerStorageUI->GetCurrentPage(), PlayerStorageIndex, tempItem);
}

