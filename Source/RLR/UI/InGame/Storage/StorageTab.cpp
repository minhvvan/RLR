// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Storage/StorageTab.h"
#include "Components/TileView.h"
#include "UI/InGame/Storage/StorageSlot.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/StorageManager.h"
#include "RLR.h"
#include "GameManager/GameplayTagManager.h"

void UStorageTab::NativeConstruct()
{
	Super::NativeConstruct();

	UStorageManager* StorageManager = GameInstance->GetStorageManager();
	if (!StorageManager)
	{
		RLR_LOG(LogRLR, Log, TEXT("StroageManager is nullptr"));
		return;
	}
}

void UStorageTab::ClearEntry()
{
	TVItem->ClearListItems();
}

void UStorageTab::SetSlotItemData(const FItemData& Item, int Idx)
{
	auto entryItem = TVItem->GetItemAt(Idx);
	UStorageSlot* itemSlot = Cast<UStorageSlot>(TVItem->GetEntryWidgetFromItem(entryItem));

	if (!itemSlot)
	{
		RLR_LOG(LogRLR, Log, TEXT("Slot을 찾을 수 없습니다."));
		return;
	}

	itemSlot->SetItemData(Item);
}

void UStorageTab::UpdateAllItem(const TArray<FItemData>& Items, FGameplayTag Tag)
{
	int maxItemNum = StorageSlotRow * StorageSlotColumn;

	auto dataManager = GameInstance->GetDataManager();
	if (!dataManager) return;

	auto storageSlotClass = dataManager->GetWidgetClass<UStorageSlot>(TEXT("WBP_StorageSlot"));
	if (!storageSlotClass) return;

	TVItem->ClearListItems();

	auto SlotType = Tag.MatchesTag(RLRTAG.UI_Storage_User) ? ESlotType::USER_STORAGE_ITEM_SLOT : ESlotType::PLAYER_STORAGE_ITEM_SLOT;
	for (int i = 0; i < maxItemNum; i++)
	{
		auto itemWidget = Cast<UStorageSlot>(CreateWidget<UStorageSlot>(GetWorld(), storageSlotClass));

		if (Items.IsValidIndex(i))
		{
			itemWidget->SetItemData(Items[i]);
			itemWidget->SetSlotIndex(i);
			itemWidget->SetPageNum(PageNum);
			itemWidget->SetSlotType(SlotType);
		}
		
		TVItem->AddItem(itemWidget);
	}
}


void UStorageTab::UpdatedStorageCallback(int PageIndex)
{
	if (PageIndex != PageNum) return;

	UStorageManager* StorageManager = GameInstance->GetStorageManager();
	if (!StorageManager)
	{
		RLR_LOG(LogRLR, Log, TEXT("StroageManager is nullptr"));
		return;
	}

	const auto& pageItems = StorageManager->GetUserStorageItemPage(PageNum);
	UpdateAllItem(pageItems, UITag);
}

void UStorageTab::SetPageNum(int page)
{
	PageNum = page;
}

int UStorageTab::GetPageNum() const
{
	return PageNum;
}
