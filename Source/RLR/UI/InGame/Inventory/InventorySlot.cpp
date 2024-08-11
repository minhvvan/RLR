// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InGame/Inventory/InventorySlot.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "GameManager/UIManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/GameManager.h"
#include "UI/InGame/CharacterStatus/Equipment/EquipmentUI.h"
#include "UI/InGame/CharacterStatus/CharacterStatusUI.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/DraggableWidget.h"
#include "UI/BaseDragDropOperation.h"
#include "UI/InGame/Inventory/ItemInformation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"



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
	if(Ret == false)
		return false;

	//따로 분류탭에 들어가 있으면 슬롯은 옮길 수 없다.
	if (Inventory->CurrentFilter != EItemType::NONE)
		return false;

	UBaseDragDropOperation* Operation = CheckValidAndType(InOperation, ESlotType::INVENTORY_SLOT);
	if(IsValid(Operation) == false)
		return false;

	UInventorySlot* DraggedSlot = Cast<UInventorySlot>(Operation->Master);
	if(IsValid(DraggedSlot) == false)
		return false;

	/*
		임시 코드
		서버에 아이템 옮겼다는 패킷 보내주기.
	*/

	//만약 옮긴 슬롯에 다른 아이템이 들어가 있다면, 서로 슬롯 위치를 바꿔준다.
	if (IsEmpty() == false)
	{
		/*
			A->B 
			B->A
		*/
		GetGameManager()->GetInventoryManager()->ChangeItemSlot(GetItemData().ITEM_SEQ, Operation->Master->SlotIndex);
		GetGameManager()->GetInventoryManager()->ChangeItemSlot(Operation->GetItemData().ITEM_SEQ, SlotIndex);
	}
	else
	{
		GetGameManager()->GetInventoryManager()->ChangeItemSlot(Operation->GetItemData().ITEM_SEQ, SlotIndex);
		//SetItemData(Operation->GetItemData());
		DraggedSlot->Clear();
	}

	//슬롯을 정확하게 옮겼으면, 기존 자리에 있던 슬롯은 깨끗하게 비워준다.
	Inventory->RefreshUI();

	return true;
}

void UInventorySlot::RefreshUI()
{
	Super::RefreshUI();


	if (GetItemData() == FItemData::EmptyItemData)
	{
		DisplayEquippedItems(false);
		return;
	}

	DisplayEquippedItems(GetItemData().IsEquiped);
}

void UInventorySlot::OnClickedSlotButton()
{
	Super::OnClickedSlotButton();

	/*
		1.서버에 장착 Req 패킷을 날려준다. 
			PacketHandler->SendEquipItemPacket(ItemData)

		2.서버에서 Equip Item 패킷을 다시 날리면 EquipmentUI에서 해당 슬롯 정보를 업데이트 해준다.
	*/
	if (IsEmpty() == true)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("해당 슬롯에는 아이템 정보가 없습니다."));
		return;
	}

	FString ItemName = GetItemData().NAME;
	UUtilBlueprintFunctionLibrary::DebugLog(ItemName);


	/*
		임시 코드.
		원래라면 서버에 패킷을 보내고 끝내야 하지만, 지금은 서버가 준비가 안되었으므로 클라 내부에서 자체적으로 처리.
	*/

	UInGameMainUI* MainUI = Cast<UInGameMainUI>(GetUIManager()->GetMainUI());
	if (MainUI)
	{
		UGameManager* GM = Cast<UGameManager>(GetGameInstance());
		if (GM)
		{
			GM->GetInventoryManager()->ItemData[GetItemData().ITEM_ID].IsEquiped = true;
		}
		MainUI->CharacterStatusUI->EquipmentUI->EquipItem(GetItemData());
		MainUI->InventoryUI->RefreshUI();
	}
}

void UInventorySlot::OnHoveredSlotButton()
{
	Super::OnHoveredSlotButton();


	if (IsEmpty() == true)
		return;

	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (!GM) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (UIManager == nullptr) return;

	UIManager->OpenSubUINearTargetSlot(this, EUIType::ITEMINFOMATION);
}

void UInventorySlot::OnUnHoveredSlotButton()
{
	Super::OnUnHoveredSlotButton();
	

	if (IsEmpty() == true)
		return;

	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (!GM) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (UIManager == nullptr) return;

	UIManager->CloseSubUI(EUIType::ITEMINFOMATION);
}


void UInventorySlot::Clear()
{
	Super::Clear();
}
