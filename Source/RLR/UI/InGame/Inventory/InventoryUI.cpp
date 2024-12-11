// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/InGame/Inventory/InventorySlot.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/GridPanel.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/GameplayTagManager.h"
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

	SetUITag(RLRTAG.UI_Inventory);

	UInventoryManager* InventoryManager = GetGameInstance()->GetSubsystem<UInventoryManager>();

	if (IsValid(InventoryManager) == false)
		return;

	InventoryManager->OnUpdateInventoryDelegate.AddUniqueDynamic(this, &UInventoryUI::RefreshUI);
	InventoryManager->OnUpdateGoldAndCashDelegate.AddUniqueDynamic(this, &UInventoryUI::RefreshGoldAndCashUI);

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

	auto InventoryManager = GetInventoryManager();

	for (int32 Count = 0; Count < MaxInventorySlotCount; Count++)
	{
		UInventorySlot* NewSlot = CreateWidget<UInventorySlot>(this, InventorySlotClass);
		NewSlot->OnSlotClicked.AddUniqueDynamic(InventoryManager, &UInventoryManager::OnInventorySlotClicked);
		NewSlot->OnSlotShiftClicked.AddUniqueDynamic(InventoryManager, &UInventoryManager::OnInventorySlotShiftClicked);
		NewSlot->OnSlotAltClicked.AddUniqueDynamic(InventoryManager, &UInventoryManager::OnInventorySlotAltClicked);
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
	const auto& ItemList = InventoryManager->GetItemList();
	for (int i = 0; i < ItemList.Num(); i++)
	{
		if(i >= MaxInventorySlotCount || i < 0 ) continue;
		
		InventorySlotList[i]->SetItemData(ItemList[i]);
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

	UInventoryManager* InventoryManager = GetGameInstance()->GetSubsystem<UInventoryManager>();
	if (IsValid(InventoryManager) == false)
		return;
	const auto& ItemList = InventoryManager->GetItemList();
	for (int i = 0; i < ItemList.Num(); i++)
	{
		if(ItemType != ItemList[i].TYPE) continue;
		InventorySlotList[i]->SetItemData(ItemList[i]);
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

void UInventoryUI::SetSlotType(ESlotType SlotType)
{
	for (auto slot : InventorySlotList)
	{
		slot->SetSlotType(SlotType);
	}
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

void UInventoryUI::SelectSlot(int32 SlotIndex)
{
	auto slot = Cast<UInventorySlot>(InventorySlotList[SlotIndex]);
	if (!slot) return;

	slot->OnSelected();
}

void UInventoryUI::CancelSelectSlot(int32 SlotIndex)
{
	auto slot = Cast<UInventorySlot>(InventorySlotList[SlotIndex]);
	if (!slot) return;

	slot->CancelSelected();
}