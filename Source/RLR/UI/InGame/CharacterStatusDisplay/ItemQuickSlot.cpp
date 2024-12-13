// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/CharacterStatusDisplay/ItemQuickSlot.h"
#include "UI/BaseDragDropOperation.h"

#include "Blueprint/UserWidget.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

#include "GameManager/InventoryManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"

#include "UI/InGame/CharacterProfile/Equipment/EquipmentUI.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/InGame/Inventory/ItemInformation.h"
#include "UI/BaseDragDropOperation.h"
#include "UI/DraggableWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Player/PlayerCommands.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


void UItemQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();
	SetSlotType(ESlotType::ITEM_QUICK_SLOT);
	Clear();
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

	DraggedWidget->SlotImage->SetBrushFromTexture(GetItemResourceData().ItemImage);

	DragDropOperation = Cast<UBaseDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(DragDropOperationClass));
	DragDropOperation->DefaultDragVisual = DraggedWidget;
	DragDropOperation->Pivot = EDragPivot::MouseDown;

	DragDropOperation->Master = this;
	DragDropOperation->DragOffset = DragOffset;
	DragDropOperation->ItemData = GetItemData();
	DragDropOperation->DragedSlotType = ESlotType::ITEM_QUICK_SLOT;

	OutOperation = DragDropOperation;
	Clear();
}

bool UItemQuickSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Ret = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if(Ret == false)
		return false;

	UBaseDragDropOperation* Operation = CheckValidAndType(InOperation, ESlotType::INVENTORY_SLOT, ESlotType::ITEM_QUICK_SLOT);
	if(IsValid(Operation) == false)
		return false;

	//받은 아이템 정보가 소모품이 아닐 경우, 응답하지 않는다.
	if(Operation->ItemData.TYPE != ItemType::Consumption)
		return false;

	//인벤토리에서 드래그 된 거면 아이템 정보만 설정해주고,
	if(Operation->DragedSlotType == ESlotType::INVENTORY_SLOT)
	{ 
		SetItemData(Operation->ItemData);
	}
	//다른 퀙 슬롯에서 가져온 거면, 가져왔던 퀵 슬롯을 비워준다.
	else if(Operation->DragedSlotType == ESlotType::ITEM_QUICK_SLOT)
	{
		Operation->Master->Clear();
		SetItemData(Operation->ItemData);
	}

	/*
		TODO
		퀵 슬롯 설정 정보를 저장할 수 있게 해주기
		퀵슬롯은 딱히 서버에 보내줄 패킷이 없다. 다만 필요한 건 키 입력과 연결을 해줘야 한다.
	*/
	{
		//GetNetworkManager()->SendChangeItemQuickSlotPacket(GetItemData(), GetSlotIndex());
	}

	return true;
}

void UItemQuickSlot::RefreshUI()
{
	Super::RefreshUI();

	URLRInputConfig* Config = GameInstance->GetDataManager()->GetInputConfig();
	if (Config)
	{
		FString InputString = Config->FindInputTagByActionTag(ActionTag).GetTagName().ToString();
		FString Prefix = TEXT("Input.");

		// 'Input.' 이후의 문자열을 추출
		int32 PrefixLength = Prefix.Len();
		FString AfterPrefix = InputString.Mid(PrefixLength);

		KeyBindingText->SetText(FText::FromString(AfterPrefix));
	}

	const FItemData& ItemData = GetItemData();
	const FItemResource& ItemResourceData = GetItemResourceData();

	if (ItemData == FItemData::EmptyItemData)
	{
		SetSlotImage(GetDefaultSlotImage());
		return;
	}

	SetSlotImage(ItemResourceData.ItemImage);
}

void UItemQuickSlot::Clear()
{
	Super::Clear();
}

void UItemQuickSlot::UpdatedItemQuickSlot()
{
	if (IsEmpty() == true)
		return;

	FText DebugText = FText::Format(FText::FromString("Update Item Quick Slot {0}"), GetItemData().NAME);
	Util::DebugLog(DebugText.ToString());
}

void UItemQuickSlot::SetActionTag(FGameplayTag NewActionTag)
{
	ActionTag = NewActionTag;
}
