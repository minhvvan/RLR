// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/CharacterStatusDisplay/ItemQuickSlotContainer.h"
#include "UI/InGame/CharacterStatusDisplay/ItemQuickSlot.h"

#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"
#include "GameOptionData/GameOptionData.h"

#include "Components/GridPanel.h"

void UItemQuickSlotContainer::NativeConstruct()
{
	Super::NativeConstruct();

}

void UItemQuickSlotContainer::Init()
{
	Super::Init();

	TSubclassOf<UItemQuickSlot> SlotClass = GetWidgetClass<UItemQuickSlot>("WBP_ItemQuickSlot");
	if (CHECK_VALID(SlotClass) == false)
		return;

	UGameOptionData* GameOption = GameInstance->GetGameOptionData();
	if (CHECK_VALID(GameOption) == false)
		return;

	ItemQuickSlotGridPanel->ClearChildren();
	const TMap<FGameplayTag, int32>& QucikSlotList = GameOption->GetItemQuickSlotOption().ItemQuickSlotList;

	int32 SlotCount = 0;
	for (TTuple<FGameplayTag, int32> Element : QucikSlotList)
	{
		UItemQuickSlot* QuickSlot = CreateWidget<UItemQuickSlot>(this, SlotClass);
		ItemQuickSlotGridPanel->AddChildToGrid(QuickSlot, SlotCount / MaxColunm, SlotCount % MaxColunm);

		FGameplayTag ActionTag = Element.Key;
		QuickSlot->SetActionTag(ActionTag);
		QuickSlot->Clear();

		QuickSlot->SetSlotIndex(SlotCount++);
		QuickSlotMap.Add(ActionTag, QuickSlot);
	}
}

void UItemQuickSlotContainer::RefreshUI()
{
	Super::RefreshUI();

	Clear();

	UGameOptionData* GameOption = GameInstance->GetGameOptionData();
	const TMap<FGameplayTag, int32>& QucikSlotList = GameOption->GetItemQuickSlotOption().ItemQuickSlotList;

	for (TTuple<FGameplayTag, int32> Iter : QucikSlotList)
	{
		FGameplayTag ActionTag = Iter.Key;
		int32		 ItemSeq = Iter.Value;

		if (QuickSlotMap.Contains(ActionTag) == false)
			continue;

		UItemQuickSlot* QuickSlot = QuickSlotMap[ActionTag];

		FItemData ItemData = GetDataManager()->GetItemData(ItemSeq);
		if (ItemData == FItemData::EmptyItemData)
		{
			QuickSlot->RefreshUI();
			continue;
		}
		QuickSlot->SetItemData(ItemData);
		
		FItemResource ItemResourceData = GetDataManager()->GetItemResource(ItemSeq);
		if (ItemResourceData == FItemResource::EmptyItemResource)
		{
			QuickSlot->RefreshUI();
			continue;
		}
	}
}

void UItemQuickSlotContainer::Clear()
{
	Super::Clear();

	for (TTuple<FGameplayTag, UItemQuickSlot*> Iter : QuickSlotMap)
	{
		UItemQuickSlot* QuickSlot = Iter.Value;
		QuickSlot->Clear();
	}
}
