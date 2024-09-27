// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Post/InputTransactionCost.h"
#include "GameManager/PostalManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "Structs/UtilStructs.h"
#include "Components/GridPanel.h"
#include "Components/EditableTextBox.h"
#include "Components/MultiLineEditableText.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void UPostOverlayUI::NativeConstruct()
{
	Super::NativeConstruct();

	SetUIType(EUIType::POST_UI);
	SetUITag(FGameplayTagManager::Get().UI_Post);

	if (ReceivedPostButton)
		ReceivedPostButton->OnClicked.AddDynamic(this, &UPostOverlayUI::OnReceivedPostButtonClicked);
	if (SentPostButton)
		SentPostButton->OnClicked.AddDynamic(this, &UPostOverlayUI::OnSentPostButtonClicked);
	if (WritePostButton)
		WritePostButton->OnClicked.AddDynamic(this, &UPostOverlayUI::OnWritePostButtonClicked);
}

void UPostOverlayUI::Init()
{
	auto dataManager = GameInstance->GetDataManager();
	if (!dataManager) return;

	TSubclassOf<UPostItemSlot> PostItemSlotClass = dataManager->GetWidgetClass<UPostItemSlot>("WBP_PostItemSlot");
	
	PostWriteTabWidget->PostSlotList.Empty();
	PostWriteTabWidget->PostSlotList.Init(nullptr, MaxPostSlotCount);

	if (PostItemSlotClass == nullptr)
	{
		DEBUG_MESSAGE;
		return;
	}

	for (int32 Count = 0; Count < MaxPostSlotCount; Count++)
	{
		UPostItemSlot* NewSlot = CreateWidget<UPostItemSlot>(this, PostItemSlotClass);
		PostWriteTabWidget->PostSlotList[Count] = NewSlot;
		NewSlot->SlotIndex = Count;
		NewSlot->PostUI = this;

		PostWriteTabWidget->PostSlotGridPanel->AddChildToGrid(NewSlot, 0, Count);
	}
}

void UPostOverlayUI::RefreshUI()
{
	UPostalManager* PostalManager = GameInstance->GetPostalManager();

	for (UPostItemSlot* ItemSlot : PostWriteTabWidget->PostSlotList)
	{
		ItemSlot->Clear();
	}

	//인벤토리 매니저가 들고 있는 데이터를  UI로 출력한다.
	TArray<FItemData> ItemList;
	PostalManager->GetItemList(ItemList);
	TArray<FItemResource> ItemResourceList;
	PostalManager->GetItemResourceList(ItemResourceList);

	// ItemResource를 ITEM_SEQ로 빠르게 찾기 위한 맵 생성
	TMap<int32, FItemResource> ItemResourceMap;
	for (const FItemResource& ItemResource : ItemResourceList)
	{
		ItemResourceMap.Add(ItemResource.ITEM_SEQ, ItemResource);
	}

	int32 ItemCount = 0;
	for (FItemData& ItemData : ItemList)
	{
		//설정된 값보다 아이템 수가 많으면 에러
		if (MaxPostSlotCount <= ItemCount)
		{
			UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UInventoryUI::RefreshUI Error. 인벤토리 슬롯보다 아이템 정보가 많습니다."));
			break;
		}

		ItemCount++;

		int32 ItemSlotIndex = ItemData.ITEM_SLOT_IDX;
		if (ItemSlotIndex >= MaxPostSlotCount || ItemSlotIndex < 0)
			continue;
		PostWriteTabWidget->PostSlotList[ItemData.ITEM_SLOT_IDX]->SetItemData(ItemData);

		const FItemResource* FoundItemResource = ItemResourceMap.Find(ItemData.ITEM_SEQ);
		if (FoundItemResource)
		{
			PostWriteTabWidget->PostSlotList[ItemData.ITEM_SLOT_IDX]->SetSlotItemResourceData(*FoundItemResource);
		}
	}
}

void UPostOverlayUI::OnReceivedPostButtonClicked()
{
	if (PostWidgetSwitcher)
	{
		PostWidgetSwitcher->SetActiveWidgetIndex(0);
	}
}

void UPostOverlayUI::OnSentPostButtonClicked()
{
	if (PostWidgetSwitcher)
	{
		PostWidgetSwitcher->SetActiveWidgetIndex(1);
	}
}

void UPostOverlayUI::OnWritePostButtonClicked()
{
	if (PostWidgetSwitcher)
	{
		PostWidgetSwitcher->SetActiveWidgetIndex(2);
	}
}

void UPostOverlayUI::SetMaxSlotCount(int32 Count)
{
	MaxPostSlotCount = Count;
	Init();
	RefreshUI();
}