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
	Clear();

	if (ItemButton)
	{
		ItemButton->OnClicked.AddUniqueDynamic(this, &UInventorySlot::OnClickedItemSlot);
		ItemButton->OnHovered.AddUniqueDynamic(this, &UInventorySlot::OnHoveredItemSlot);
		ItemButton->OnUnhovered.AddUniqueDynamic(this, &UInventorySlot::OnUnHoveredItemSlot);
	}
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);


	//비어있는 슬롯은 옮기지 않는다.
	if(IsEmpty())
		return;

	if (IsValid(DraggableWidgetClass) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UInventorySlot::NativeOnDragDetected Error. DraggableWidgetClass 정보가 없습니다. "));
		return;
	}

	if (IsValid(DragDropOperationClass) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UInventorySlot::NativeOnDragDetected Error. DragDropOperationClass 정보가 없습니다. "));
		return;
	}

	DraggedWidget = CreateWidget<UDraggableWidget>(this, DraggableWidgetClass);
	
	DraggedWidget->SlotImage->SetBrushFromTexture(GetItemData().ItemImage);



	DragDropOperation = Cast<UBaseDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(DragDropOperationClass));
	DragDropOperation->DefaultDragVisual = DraggedWidget;
	DragDropOperation->Pivot = EDragPivot::MouseDown;
	
	DragDropOperation->Master = this;
	DragDropOperation->DragOffset = DragOffset;
	DragDropOperation->ItemData = GetItemData();
	DragDropOperation->StartingDragType = EDragType::INVENTORY_SLOT;

	OutOperation = DragDropOperation;
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Ret = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if(Ret == false)
		return false;


	UBaseDragDropOperation* Operation = CheckValidAndType(InOperation, EDragType::INVENTORY_SLOT);
	if(IsValid(Operation) == false)
		return false;

	UInventorySlot* DraggedSlot = Cast<UInventorySlot>(Operation->Master);
	if(IsValid(DraggedSlot) == false)
		return false;

	/*
		임시 코드
		서버에 아이템 옮겼다는 패킷 보내주기.
	*/


	GetGameManager()->GetInventoryManager()->ChangeItemSlot(DraggedSlot->GetItemData().ITEM_SEQ, SlotIndex);

	SetItemData(DraggedSlot->GetItemData());
	//슬롯을 정확하게 옮겼으면, 기존 자리에 있던 슬롯은 깨끗하게 비워준다.
	DraggedSlot->Clear();

	return true;
}

void UInventorySlot::OnClickedItemSlot()
{
	/*
		1.서버에 장착 Req 패킷을 날려준다. 
			PacketHandler->SendEquipItemPacket(ItemData)

		2.서버에서 Equip Item 패킷을 다시 날리면 EquipmentUI에서 해당 슬롯 정보를 업데이트 해준다.
	*/
	if (SlotItemData.ITEM_ID == -1)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("해당 슬롯에는 아이템 정보가 없습니다."));
		return;
	}

	FString ItemName = SlotItemData.NAME;
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
			GM->GetInventoryManager()->ItemData[SlotItemData.ITEM_ID].IsEquiped = true;
		}
		MainUI->CharacterStatusUI->EquipmentUI->EquipItem(SlotItemData);
		MainUI->InventoryUI->RefreshUI();
	}
}

void UInventorySlot::OnHoveredItemSlot()
{
	if (IsEmpty() == true)
		return;

	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (!GM) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (UIManager == nullptr) return;

	UIManager->OpenSubUINearTargetSlot(this);
}

void UInventorySlot::OnUnHoveredItemSlot()
{
	if (IsEmpty() == true)
		return;

	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (!GM) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (UIManager == nullptr) return;

	UIManager->CloseSubUINearTargetSlot();
}

void UInventorySlot::SetItemData(FItemData ItemData)
{
	//슬롯 정보를 업데이트 해준다.


	SlotItemData = ItemData;

	UTexture2D* Texture = ItemData.ItemImage;
	if (IsValid(Texture) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UInventorySlot::SetItemData Error. 텍스쳐 정보가 없습니다."));
		return;
	}
	SlotImage->SetBrushFromTexture(Texture, true);
	DisplayEquippedItems(ItemData.IsEquiped);

	//아이템 등급에 따른 배경 이미지 색깔 추가해주기.

}

void UInventorySlot::Clear()
{
	Super::Clear();

	if (IsValid(DefaultSlotImage) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UInventorySlot::Clear Error. Default Slot Image가 없습니다."));
		return;
	}

	SlotImage->SetBrushFromTexture(DefaultSlotImage, true);
	SlotItemData = FItemData();
}
