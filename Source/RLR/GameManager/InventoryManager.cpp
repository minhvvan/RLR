// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/InventoryManager.h"

#include "UIManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/StorageManager.h"
#include "GameManager/GameplayTagManager.h"

#include "Structs/ItemStructs.h"

#include "Components/WidgetSwitcher.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "UI/SlotUI.h"
#include "UI/InGame/Trade/TradeUI.h"
#include "UI/InGame/Shop/NPCShopUI.h"
#include "UI/InGame/Shop/NPCSaleTab.h"
#include "UI/InGame/Storage/StorageUI.h"
#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/PostWriteTabWidget.h"
#include "UI/InGame/Inventory/InventoryUI.h"


void UInventoryManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UpdatedItemSettingDelegate.Clear();
	UpdatedTryUsingItemAction.Clear();
	OnUpdateInventoryDelegate.Clear();
	OnUpdateEquipDelegate.Clear();

	InventoryItemData.SetNum(50);
}

void UInventoryManager::Update()
{
	OnUpdateInventoryDelegateBroadcast();
}

void UInventoryManager::AddItem(const FItemData& NewItem, int SlotIndex)
{
	if (NewItem == FItemData::EmptyItemData)
	{
		DEBUG_LOG("Add Item Warning Message. NewItem is empty.");
		return;
	}

	if (SlotIndex == -1)
	{
		for (int i = 0; i < InventoryItemData.Num(); i++)
		{
			if (InventoryItemData[i] == FItemData::EmptyItemData)
			{
				InventoryItemData[i] = NewItem;
				break;
			}
		}
	}
	else
	{
		InventoryItemData[SlotIndex] = NewItem;
	}
	
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
		
		AddItem(NewItem);
	}
	
	OnUpdateInventoryDelegateBroadcast();
}

const FItemData& UInventoryManager::GetItem(int32 Item_ID)
{
	for (auto& item : InventoryItemData)
	{
		if (item.ITEM_ID == Item_ID)
		{
			return item;
		}
	}

	return FItemData::EmptyItemData;
}

const TArray<FItemData>& UInventoryManager::GetItemList() const
{
	return InventoryItemData;
}

void UInventoryManager::RemoveItem(int32 Item_ID)
{
	for (auto& item : InventoryItemData)
	{
		if (item.ITEM_ID == Item_ID)
		{
			InventoryItemData.Remove(item);
			break;
		}
	}
}

void UInventoryManager::RemoveItem(int32 Item_ID, int Amount)
{
	for (auto& item : InventoryItemData)
	{
		if ( item.ITEM_ID == Item_ID)
		{
			item.ITEM_QUANTITY -= Amount;
			if (item.ITEM_QUANTITY == 0) item = FItemData::EmptyItemData;
			break;
		}
	}
	
	
	OnUpdateInventoryDelegateBroadcast();
}

bool UInventoryManager::EquipItem( FItemData& equipItem)
{
	equipItem.IsEquiped = true;
	OnUpdateEquipDelegateBroadcast(equipItem);
	return true;
}

bool UInventoryManager::UnEquipItem( FItemData& equipItem)
{
	equipItem.IsEquiped = false;
	OnUpdateEquipDelegateBroadcast(equipItem);
	return true;
}

void UInventoryManager::SetItemSlot(const FItemData& NewItem, int32 NewSlotIndex)
{
	InventoryItemData[NewSlotIndex] = NewItem;
	OnUpdateInventoryDelegateBroadcast();
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

UInventorySlot* UInventoryManager::GetInventorySlot(int32 InventorySlotIndex)
{
	UInventoryUI* Inventory = GameInstance->GetUIManager()->GetSubUI<UInventoryUI>(RLRTAG.UI_Inventory);
	if (InventorySlotIndex + 1 >= Inventory->InventorySlotList.Num()) return nullptr;
	return Inventory->InventorySlotList[InventorySlotIndex];
}

void UInventoryManager::OnInventorySlotClicked(int32 SlotIndex, const FItemData& ItemData, ESlotType SlotType)
{
	switch (SlotType)
	{
	case ESlotType::INVENTORY_SLOT:
		GameInstance->GetNetworkManager()->SendEquipChangePacket(ItemData, SlotIndex);
		break;
	case ESlotType::STORAGE_INVENTORY_SLOT:
		GameInstance->GetStorageManager()->SendPktMoveItemInventoryToStorage(ItemData, ItemData.ITEM_QUANTITY, ESlotType::USER_STORAGE_ITEM_SLOT);
		break;
	case ESlotType::NPCSHOP_INVENTORY_SLOT:
		{
			/* 아이템 개수가 2개 이상이라면, shift+우클릭을 하지 않더라도 번들 판매 UI 출력 */
			auto UIManager = GameInstance->GetUIManager();
			auto NPCShop = UIManager->GetSubUI<UNPCShopUI>(RLRTAG.UI_NPCShop);
			if (ItemData.ITEM_QUANTITY > 1)
			{
				NPCShop->GetSaleTab()->OpenBundleSell(ItemData, SlotIndex);
			}
			else
			{
				NPCShop->AddSaleItem(ItemData, SlotIndex);
			}
		}
		break;
	case ESlotType::POST_INVENTORY_SLOT:
		{
			/* Post 에서 인벤토리 슬롯 우클릭 시 첨부아이템 슬롯으로 아이템 이동 */
			auto UIManager = GameInstance->GetUIManager();
			auto PostUI = UIManager->GetSubUI<UPostOverlayUI>(RLRTAG.UI_Post);
			if (!PostUI) return;

			UPostWriteTabWidget* PostWriteWidget = PostUI->PostWriteTabWidget;
			if (PostUI->PostWidgetSwitcher->GetActiveWidget() != PostWriteWidget) return;

			
			if (ItemData.ITEM_QUANTITY > 1)
			{
				/* 아이템 개수가 2개 이상이라면, 번들 첨부 UI 출력 */
				PostUI->PostWriteTabWidget->OpenBundleItemSend(ItemData, SlotIndex);
			}
			else
			{
				PostUI->PostWriteTabWidget->AddItemToPostSlot(ItemData, SlotIndex);
			}
		}
		break;
	case ESlotType::TRADE_INVENTORY_SLOT:
		{
			/* 아이템 개수가 2개 이상이라면, shift+우클릭을 하지 않더라도 번들 판매 UI 출력 */
			auto UIManager = GameInstance->GetUIManager();
			auto TradeUI = UIManager->GetSubUI<UTradeUI>(RLRTAG.UI_Trade);
			//if (ItemData.ITEM_QUANTITY > 1)
			//{
			//	TradeUI->OpenBundleTrade(ItemData, SlotIndex);
			//}
			//else
			//{
			//	TradeUI->AddSaleItem(ItemData, SlotIndex);
			//}
		}
		break;
	default:
		break;
	}
}

void UInventoryManager::OnInventorySlotShiftClicked(int32 SlotIndex, const FItemData& ItemData, ESlotType SlotType)
{
	switch (SlotType)
	{
	case ESlotType::STORAGE_INVENTORY_SLOT:
		if (auto UIManager = GameInstance->GetUIManager())
		{
			if (auto storageUI = UIManager->GetSubUI<UStorageUI>(RLRTAG.UI_Storage_User))
			{
				storageUI->InventorySlotShiftClicked(ItemData);
			}
		}
		
		break;
	default:
		break;
	}
}

void UInventoryManager::OnInventorySlotAltClicked(int32 SlotIndex, const FItemData& ItemData, ESlotType SlotType)
{
	switch (SlotType)
	{
	case ESlotType::STORAGE_INVENTORY_SLOT:
		GameInstance->GetStorageManager()->SendPktMoveItemInventoryToStorage(ItemData, ItemData.ITEM_QUANTITY, ESlotType::PLAYER_STORAGE_ITEM_SLOT);
		break;
	default:
		break;
	}
}

void UInventoryManager::OnInventorySlotShiftRightClicked(int32 SlotIndex, const FItemData& ItemData, ESlotType SlotType)
{
	switch (SlotType)
	{
	case ESlotType::NPCSHOP_INVENTORY_SLOT:
		auto UIManager = GameInstance->GetUIManager();
		auto NPCShop = UIManager->GetSubUI<UNPCShopUI>(RLRTAG.UI_NPCShop);
		NPCShop->GetSaleTab()->OpenBundleSell(ItemData, SlotIndex);
		break;
	}
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

const FSkillDictionary<FGameplayTag, FItemData>& UInventoryManager::GetOwnItems()
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
void UInventoryManager::ResetItemList()
{
	// 모든 슬롯을 EmptyItemData로 초기화
	for (int i = 0; i < InventoryItemData.Num(); i++)
	{
		InventoryItemData[i] = FItemData::EmptyItemData;
	}

	// UI 업데이트
	OnUpdateInventoryDelegateBroadcast();
}
void UInventoryManager::SetQuickSlotItems(TArray<FItemData>& SelectedItems)
{
	// GameplayTagManager
	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	const FGameplayTagContainer* ItemTags = TagManager.GetItemTags();
	ItemQuickSlots.Empty();

	for (int i = 0; i < SelectedItems.Num(); i++)
	{
		const FItemData& Data = SelectedItems[i];
		if (Data == FItemData::EmptyItemData) continue;

		//TODO: SelectedItems는 QuickSlot개수와 동일하게(비어있는 Item은 EmptyItem으로)
		FGameplayTag ItemTag = ItemTags->GetByIndex(i);
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

void UInventoryManager::OnInventorySlotShiftClickedDelegateBroadcast(const FItemData& SlotItemData)
{
	OnInventorySlotShiftClickedDelegate.ExecuteIfBound(SlotItemData);
}