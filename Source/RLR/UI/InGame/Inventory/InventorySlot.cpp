// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InGame/Inventory/InventorySlot.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "GameManager/UIManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/StorageManager.h"

#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/DraggableWidget.h"
#include "UI/BaseDragDropOperation.h"



void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
	SetSlotType(ESlotType::INVENTORY_SLOT);
	Clear();
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	//따로 분류탭에 들어가 있으면 슬롯은 옮길 수 없다.
	if (Inventory->CurrentFilter != ItemType::None)
		return;

	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Ret = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if(Ret == false) return false;
	
	//따로 분류탭에 들어가 있으면 슬롯은 옮길 수 없다.
	if (Inventory->CurrentFilter != ItemType::None) 
		return Ret;
	
	UBaseDragDropOperation* Operation = Cast<UBaseDragDropOperation>(InOperation);
	if (!Operation)

	{
		RLR_LOG(LogRLR, Log, TEXT("Operation is nullptr"));
		return Ret;
	}
	
	const auto& itemData = Operation->ItemData;
	if (itemData == FItemData::EmptyItemData || itemData.ITEM_QUANTITY == 0)
	{
		RLR_LOG(LogRLR, Log, TEXT("itemData is EmptyData"));
		return Ret; 
	}
	
	if(Operation->DragedSlotType == ESlotType::INVENTORY_SLOT ||
		Operation->DragedSlotType == ESlotType::STORAGE_INVENTORY_SLOT)
	{
		UInventorySlot* DraggedSlot = Cast<UInventorySlot>(Operation->Master);
		if(IsValid(DraggedSlot) == false) return false;
		/*
			임시 코드
			서버에 아이템 옮겼다는 패킷 보내주기.
		*/

		//만약 옮긴 슬롯에 다른 아이템이 들어가 있다면, 서로 슬롯 위치를 바꿔준다.
		GetGameManager()->GetInventoryManager()->SetItemSlot(GetItemData(), Operation->Master->SlotIndex);
		GetGameManager()->GetInventoryManager()->SetItemSlot(Operation->GetItemData(), SlotIndex);
	}
	else if (Operation->DragedSlotType == ESlotType::USER_STORAGE_ITEM_SLOT
		|| Operation->DragedSlotType == ESlotType::PLAYER_STORAGE_ITEM_SLOT)
	{
		GetStorageManager()->SendPktMoveItemStorageToInventory(itemData, itemData.ITEM_QUANTITY, Operation->DragedSlotType, Operation->SlotIndex, SlotIndex);
	}

	return Ret;
}

void UInventorySlot::RefreshUI()
{
	Super::RefreshUI();

	FItemData item = GetItemData();
	if (item == FItemData::EmptyItemData || item.ITEM_QUANTITY == 0)
	{
		DisplayEquippedItems(false);
		ItemNameText->SetText(FText());
		SetSlotImage(GetDefaultSlotImage());

		UUIManager* UIManager = GameInstance->GetUIManager();
		if (UIManager == nullptr) return;

		FGameplayTagManager TagManager = FGameplayTagManager::Get();
		UIManager->CloseSubUI(TagManager.UI_ItemInfomation);

		return;
	}
	
	SetSlotImage(GetItemResourceData().ItemImage);
	FText FullText = FText::Format(
		FText::FromString("{0} x{1}"),
		GetItemData().NAME,
		FText::AsNumber(GetItemData().ITEM_QUANTITY)
	);
	ItemNameText->SetText(FullText);

	DisplayEquippedItems(GetItemData().IsEquiped);
}

FReply UInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (IsEmpty() == true)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("해당 슬롯에는 아이템 정보가 없습니다."));
		return result;
	}

	const FItemData& itemData = GetItemData();

	if (InMouseEvent.IsLeftShiftDown())
	{
		OnSlotShiftClicked.Broadcast(SlotIndex, itemData, SlotType);
	}
	else if (InMouseEvent.IsAltDown())
	{
		OnSlotAltClicked.Broadcast(SlotIndex, itemData, SlotType);
	}
	else
	{
		OnSlotClicked.Broadcast(SlotIndex, itemData, SlotType);
	}

	return result;
}

void UInventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (IsEmpty() == true)
		return;

	UUIManager* UIManager = GetUIManager();
	if (UIManager == nullptr) return;

	UMainUI* mainUI = UIManager->GetPage<UMainUI>(UIManager->GetActivePageTag());
	if (mainUI == nullptr) return;

	mainUI->OpenSubUINearTargetSlot(this, RLRTAG.UI_ItemInfomation);
}

void UInventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	
	UUIManager* UIManager = GameInstance->GetUIManager();
	if (UIManager == nullptr) return;

	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	UIManager->CloseSubUI(TagManager.UI_ItemInfomation);
}


void UInventorySlot::Clear()
{
	Super::Clear();
}

void UInventorySlot::OnSelected()
{
	SetIsEnabled(false);
	SlotImage->SetColorAndOpacity(SlotColors[false]);
	SlotImage->SynchronizeProperties();
}

void UInventorySlot::CancelSelected()
{
	SetIsEnabled(true);
	SlotImage->SetColorAndOpacity(SlotColors[true]);
	SlotImage->SynchronizeProperties();
}

void UInventorySlot::SetIsEnabled(bool bInIsEnabled)
{
	Super::SetIsEnabled(bInIsEnabled);
}