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
	if (Inventory->CurrentFilter != EItemType::NONE)
		return;

	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Ret = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if(Ret == false) return false;
	
	//따로 분류탭에 들어가 있으면 슬롯은 옮길 수 없다.
	if (Inventory->CurrentFilter != EItemType::NONE) return Ret;
	
	UBaseDragDropOperation* Operation = Cast<UBaseDragDropOperation>(InOperation);
	if (!Operation)
	{
		RLR_LOG(LogRLR, Log, TEXT("Operation is nullptr"));
		return Ret;
	}
	
	const auto& itemData = Operation->ItemData;
	if (itemData == FItemData::EmptyItemData || itemData.QUANTITY == 0)
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
		if (IsEmpty())
		{
			GetGameManager()->GetInventoryManager()->ChangeItemSlot(Operation->GetItemData().ITEM_ID, SlotIndex);
			DraggedSlot->Clear();
		}
		else
		{
			//swap
			GetGameManager()->GetInventoryManager()->ChangeItemSlot(GetItemData().ITEM_ID, Operation->Master->SlotIndex);
			GetGameManager()->GetInventoryManager()->ChangeItemSlot(Operation->GetItemData().ITEM_ID, SlotIndex);
		}

		//슬롯을 정확하게 옮겼으면, 기존 자리에 있던 슬롯은 깨끗하게 비워준다.
		Inventory->RefreshUI();
	}
	else 
	{
		GetStorageManager()->SendPktMoveItemStorageToInventory(itemData, itemData.QUANTITY, Operation->DragedSlotType, Operation->SlotIndex, SlotIndex);
	}

	return Ret;
}

void UInventorySlot::RefreshUI()
{
	Super::RefreshUI();

	FItemData item = GetItemData();
	if (item == FItemData::EmptyItemData || item.QUANTITY == 0)
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
	ItemNameText->SetText(GetItemData().NAME);

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
		// bool HasCustomEvent = InventoryManger->OnInventorySlotClickedDelegate.IsBound();
		// if (HasCustomEvent == true)
		// {
		// 	/*
		// 		인벤토리 슬롯을 클릭 했을 때 다른 곳에서 클릭 이벤트를 요구하고 있는가?
		// 		ex) 개인 거래창이 열렸을 때는, 인벤토리 슬롯을 누르면 개인 거래창에 아이템이 올라가야 한다.
		// 		ex) 아이템을 강화하는 UI 같은 곳에서, 인벤토리 슬롯을 누르면 강화 슬롯 위에 아이템이 올라가야 한다.
		// 	*/
		// 	InventoryManger->OnInventorySlotClickedDelegateBroadcast(itemData);
		// }
		// else if (HasCustomEvent == false)
		// {
		// 	/*
		// 		아무런 이벤트가 없으면 아이템 장착.
		// 	*/
		// 	GameInstance->GetNetworkManager()->SendEquipChangePacket(itemData);
		// }
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