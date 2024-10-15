// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/InGame/Inventory/InventorySlot.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/GridPanel.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/GameManager.h"
#include "Structs/UtilStructs.h"
#include "Structs/ItemStructs.h"

UInventoryUI::UInventoryUI(const FObjectInitializer& ObjectInitializer):
	MaxColumm(8),
	MaxInventorySlotCount(32),
	CurrentFilter(EItemType::NONE)
{
}

void UInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();

	SetUIType(EUIType::INVENTORY_UI);
	SetUITag(FGameplayTagManager::Get().UI_Inventory);

	UInventoryManager* InventoryManager = GetGameInstance()->GetSubsystem<UInventoryManager>();

	if(IsValid(InventoryManager) == false)
		return;

	InventoryManager->OnUpdateInventoryDelegate.AddDynamic(this, &UInventoryUI::RefreshUI);
	InventoryManager->OnUpdateGoldAndCashDelegate.AddDynamic(this, &UInventoryUI::RefreshGoldAndCashUI);

	AllButton->OnClicked.AddUniqueDynamic(this, &UInventoryUI::OnAllButtonClicked);
	EquipmentButton->OnClicked.AddUniqueDynamic(this, &UInventoryUI::OnEquipmentButtonClicked);
	ConsumableButton->OnClicked.AddUniqueDynamic(this, &UInventoryUI::OnConsumableButtonClicked);
	EtcItemButton->OnClicked.AddUniqueDynamic(this, &UInventoryUI::OnEtcItemButtonClicked);
}

void UInventoryUI::Init()
{
	InventoryGridPanel->ClearChildren();
	InventorySlotList.Empty();

	//슬롯 생성
	InventorySlotList.Init(nullptr, MaxInventorySlotCount);
	TSubclassOf<UInventorySlot> InventorySlotClass = GetWidgetClass<UInventorySlot>("WBP_InventorySlot");
	if(IsValid(InventorySlotClass) == false)
	{ 
		DEBUG_MESSAGE;
		return;
	}

	for (int32 Count = 0; Count < MaxInventorySlotCount; Count++)
	{
		UInventorySlot* NewSlot = CreateWidget<UInventorySlot>(this, InventorySlotClass);
		InventorySlotList[Count] = NewSlot;
		NewSlot->SlotIndex = Count;
		NewSlot->Inventory = this;
		InventoryGridPanel->AddChildToGrid(NewSlot, Count/MaxColumm, Count % MaxColumm);
	}

}

void UInventoryUI::RefreshUI()
{
	
	//장비창, 소모품창, 기타창 같이 따로 탭을 누르고 있는 중에는 전체 RefreshUI를 해주지 않는다.
	if (CurrentFilter != EItemType::NONE)
	{
		ShowItemsByType(CurrentFilter);
		return;
	}

	UInventoryManager* InventoryManager = GetGameInstance()->GetSubsystem<UInventoryManager>();

	for (UInventorySlot* ItemSlot : InventorySlotList)
	{
		ItemSlot->Clear();
	}

	//인벤토리 매니저가 들고 있는 데이터를  UI로 출력한다.
	TArray<FItemData> ItemList;
	InventoryManager->GetItemList(ItemList);

	int32 ItemCount = 0;
	for (FItemData& ItemData : ItemList)
	{
		//설정된 값보다 아이템 수가 많으면 에러
		if (MaxInventorySlotCount <= ItemCount)
		{
			UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UInventoryUI::RefreshUI Error. 인벤토리 슬롯보다 아이템 정보가 많습니다."));
			break;
		}

		ItemCount++;

		int32 ItemSlotIndex = ItemData.ITEM_SLOT_IDX;
		if(ItemSlotIndex >= MaxInventorySlotCount || ItemSlotIndex < 0 )
			continue;
		InventorySlotList[ItemData.ITEM_SLOT_IDX]->SetItemData(ItemData);
	}
}

void UInventoryUI::RefreshGoldAndCashUI()
{
	UInventoryManager* InventoryManager = GetGameInstance()->GetSubsystem<UInventoryManager>();
	if (IsValid(InventoryManager) == false)
		return;

	FText NewGold = FText::FromString(FString::FromInt(InventoryManager->GetGold()));
	GoldText->SetText(NewGold);

	FText NewSilber = FText::FromString(FString::FromInt(InventoryManager->GetSilver()));
	SilberText->SetText(NewSilber);
}

void UInventoryUI::ShowItemsByType(EItemType ItemType)
{
	/*
		선택된 속성의 아이템들만 보여준다.
	*/

	for (UInventorySlot* ItemSlot : InventorySlotList)
	{
		ItemSlot->Clear();
	}

	TArray<FItemData> ItemList;
	UInventoryManager* InventoryManager = GetGameInstance()->GetSubsystem<UInventoryManager>();
	if (IsValid(InventoryManager) == false)
		return;
	InventoryManager->GetItemList(ItemList);

	int32 ItemCount = 0;
	for (FItemData ItemData : ItemList)
	{
		if(ItemType != ItemData.TYPE)
			continue;
		
		//설정된 값보다 아이템 숫가 많으면 에러
		if (MaxInventorySlotCount <= ItemCount)
		{

			UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UInventoryUI::RefreshUI Error. 인벤토리 슬롯보다 아이템 정보가 많습니다."));
			break;
		}
		InventorySlotList[ItemCount]->SetItemData(ItemData);
	}
}

void UInventoryUI::SortItem()
{
	//아이템 정렬을 하면, 클라이언트에서 처리해도 되는 건가?

	UUtilBlueprintFunctionLibrary::DebugLog(TEXT("제작 중"));
}

void UInventoryUI::SetItemData(FItemData& NewItem)
{
	/*
		특정 슬로 아이템 셋
	*/

}

void UInventoryUI::OnAllButtonClicked()
{
	CurrentFilter = EItemType::NONE;
	RefreshUI();
}

void UInventoryUI::OnEquipmentButtonClicked()
{
	CurrentFilter = EItemType::EQUIPMENT;
	ShowItemsByType(EItemType::EQUIPMENT);
}

void UInventoryUI::OnConsumableButtonClicked()
{
	CurrentFilter = EItemType::CONSUMPTION;
	ShowItemsByType(EItemType::CONSUMPTION);
}

void UInventoryUI::OnEtcItemButtonClicked()
{
	CurrentFilter = EItemType::ETC;
	ShowItemsByType(EItemType::ETC);
}

void UInventoryUI::SetMaxSlotCount(int32 Count)
{
	MaxInventorySlotCount = Count;
	Init();
	RefreshUI();
}

void UInventoryUI::RemoveSaleItem(const FItemData& Item)
{
	auto slot = Cast<UInventorySlot>(InventorySlotList[Item.ITEM_SLOT_IDX]);
	if (!slot) return;

	slot->CancelSale();
}