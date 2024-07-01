// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/StatusDisplay/ItemQuickSlot.h"
#include "UI/BaseDragDropOperation.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "UI/InGame/CharacterStatus/Equipment/EquipmentUI.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/InGame/Inventory/ItemInformation.h"
#include "UI/BaseDragDropOperation.h"
#include "UI/DraggableWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


void UItemQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();

}

void UItemQuickSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	//비어있는 슬롯은 옮기지 않는다.
	if (IsEmpty())
		return;

	if (IsValid(DraggableWidgetClass) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UItemQuickSlot::NativeOnDragDetected Error. DraggableWidgetClass 정보가 없습니다. "));
		return;
	}

	if (IsValid(DragDropOperationClass) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UItemQuickSlot::NativeOnDragDetected Error. DragDropOperationClass 정보가 없습니다. "));
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
	DragDropOperation->StartingDragType = EDragType::ITEM_QUICK_SLOT;

	OutOperation = DragDropOperation;
}

bool UItemQuickSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Ret = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if(Ret == false)
		return false;

	UBaseDragDropOperation* Operation = CheckValidAndType(InOperation, EDragType::INVENTORY_SLOT, EDragType::ITEM_QUICK_SLOT);
	if(IsValid(Operation) == false)
		return false;

	//받은 아이템 정보가 소모품이 아닐 경우, 응답하지 않는다.
	if(Operation->ItemData.TYPE != EItemType::CONSUMPTION)
		return false;

	//인벤토리에서 드래그 된 거면 아이템 정보만 설정해주고,
	if(Operation->StartingDragType == EDragType::INVENTORY_SLOT)
	{ 
		SetItemData(Operation->ItemData);
	}
	//다른 퀙 슬롯에서 가져온 거면, 가져왔던 퀵 슬롯을 비워준다.
	else if(Operation->StartingDragType == EDragType::ITEM_QUICK_SLOT)
	{
		Operation->Master->Clear();
		SetItemData(Operation->ItemData);
	}

	/*
		TODO
		퀵 슬롯 설정 정보를 저장할 수 있게 해주기

		퀵슬롯은 딱히 서버에 보내줄 패킷이 없다. 다만 필요한 건 키 입력과 연결을 해줘야 한다.
	*/

	return true;
}

void UItemQuickSlot::Clear()
{
	Super::Clear();

	if (IsValid(DefaultSlotImage) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UItemQuickSlot::Clear Error. Default Slot Image가 없습니다."));
		return;
	}

	SlotImage->SetBrushFromTexture(DefaultSlotImage, true);
	SlotItemData = FItemData();
}

void UItemQuickSlot::SetItemData(FItemData ItemData)
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
}
