// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Storage/StorageTab.h"
#include "Components/TileView.h"
#include "UI/InGame/Storage/StorageSlot.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"
#include "RLR.h"

void UStorageTab::NativeConstruct()
{
	Super::NativeConstruct();

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

void UStorageTab::UpdateAllItem(const TArray<FItemData>& Items)
{
	int maxItemNum = StorageSlotRow * StorageSlotColumn;

	auto dataManager = GameInstance->GetDataManager();
	if (!dataManager) return;

	auto storageSlotClass = dataManager->GetWidgetClass<UStorageSlot>(TEXT("WBP_StorageSlot"));
	if (!storageSlotClass) return;

	TVItem->ClearListItems();

	for (int i = 0; i < maxItemNum; i++)
	{
		auto itemWidget = Cast<UStorageSlot>(CreateWidget<UStorageSlot>(GetWorld(), storageSlotClass));

		if (Items.IsValidIndex(i)) itemWidget->SetItemData(Items[i]);
		TVItem->AddItem(itemWidget);
	}
}
