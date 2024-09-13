// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InGame/Inventory/InventorySlot.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "GameManager/UIManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"

#include "UI/InGame/CharacterStatus/Equipment/EquipmentUI.h"
#include "UI/InGame/CharacterStatus/CharacterStatusUI.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/DraggableWidget.h"
#include "UI/BaseDragDropOperation.h"
#include "UI/InGame/Inventory/ItemInformation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Structs/UtilStructs.h"



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
	
	SetSlotImage(ItemTestImage);
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

	/*
		임시코드. 패킷 연결 확인되면 주석 처리한거 지울 예정.
	*/

	//FString ItemName = GetItemData().NAME;
	//UUtilBlueprintFunctionLibrary::DebugLog(ItemName);

	//UInGameMainUI* MainUI = Cast<UInGameMainUI>(GetUIManager()->GetMainUI());
	//if (MainUI)
	//{
	//	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	//	if (GM)
	//	{
	//		GM->GetInventoryManager()->ItemData[GetItemData().ITEM_ID].IsEquiped = true;
	//	}
	//	MainUI->CharacterStatusUI->EquipmentUI->EquipItem(GetItemData());
	//	MainUI->InventoryUI->RefreshUI();
	//}
	FItemData  itemData = GetItemData();
	GameInstance->GetNetworkManager()->SendEquipChangePacket(GetItemData());
	return result;
}

void UInventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (IsEmpty() == true)
		return;

	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (!GM) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (UIManager == nullptr) return;

	UIManager->OpenSubUINearTargetSlot(this, EUIType::ITEMINFOMATION);
}

void UInventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	
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
