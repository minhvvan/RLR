// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SlotUI.h"
#include "UI/BaseDragDropOperation.h"
#include "UI/DraggableWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/RLRStruct.h"
#include "Structs/UtilStructs.h"


void USlotUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(SlotButton) == true)
	{
		SlotButton->OnClicked.AddUniqueDynamic(this, &USlotUI::OnClickedSlotButton);
		SlotButton->OnHovered.AddUniqueDynamic(this, &USlotUI::OnHoveredSlotButton);
		SlotButton->OnUnhovered.AddUniqueDynamic(this, &USlotUI::OnUnHoveredSlotButton);
	}

}

void USlotUI::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	//비어있는 슬롯은 옮기지 않는다.
	if (IsEmpty())
		return;

	TSubclassOf<UDraggableWidget> DefaultDraggableWidgetClass = GetDraggableWidgetClass();
	if (IsValid(DefaultDraggableWidgetClass) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("SlotUI::NativeOnDragDetected Error. DraggableWidgetClass 정보가 없습니다. "));
		return;
	}
	DraggedWidget = CreateWidget<UDraggableWidget>(this, DefaultDraggableWidgetClass);

	if(IsValid(GetItemData().ItemImage) == true)
		DraggedWidget->SlotImage->SetBrushFromTexture(GetItemData().ItemImage);
	else if(IsValid(GetSkillData().SkillImage) == true)
		DraggedWidget->SlotImage->SetBrushFromTexture(GetSkillData().SkillImage);
	else
		DraggedWidget->SlotImage->SetBrushFromTexture(GetDefaultSlotImage());
	/*

	*/

	TSubclassOf<UBaseDragDropOperation> DefaultDragDropClass = GetDragDropOperationClass();
	if (IsValid(DefaultDraggableWidgetClass) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("SlotUI::NativeOnDragDetected Error. DraggableWidgetClass 정보가 없습니다. "));
		return;
	}
	UBaseDragDropOperation* CopyOperation = Cast<UBaseDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(DefaultDragDropClass));

	CopyOperation->DefaultDragVisual = DraggedWidget;
	CopyOperation->Pivot = EDragPivot::MouseDown;
	CopyOperation->DragOffset = DragOffset;
	CopyOperation->SetItemData(GetItemData());
	CopyOperation->SetSkillData(GetSkillData());
	CopyOperation->SetMaster(this);
	CopyOperation->DragedSlotType = GetSlotType();
	OutOperation = CopyOperation;

}

bool USlotUI::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);


	UBaseDragDropOperation* Operation = Cast<UBaseDragDropOperation>(InOperation);
	if(IsValid(Operation) == false)
		return false;

	if (Operation->Master == this)
		return false;

	return true;
}

void USlotUI::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

}

FReply USlotUI::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

	FVector2D MousePos = InMouseEvent.GetScreenSpacePosition();
	DragOffset = InGeometry.AbsoluteToLocal(MousePos);

	FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	return ReplyResult.NativeReply;
}

void USlotUI::OnClickedSlotButton()
{

}

void USlotUI::OnHoveredSlotButton()
{
}

void USlotUI::OnUnHoveredSlotButton()
{
}

void USlotUI::SetSlotImage(UTexture2D* NewImage)
{
	if (IsValid(NewImage) == false)
	{
		SlotImage->SetBrushFromTexture(GetDefaultSlotImage());
	}

	SlotImage->SetBrushFromTexture(NewImage);
}

void USlotUI::Clear()
{
	SlotImage->SetBrushFromTexture(GetDefaultSlotImage());
	if (IsValid(GetSlotData()) == true)
	{
		GetSlotData()->Clear();
	}
	RefreshUI();
}

bool USlotUI::IsEmpty()
{
	if(IsValid(DragDropOperation) == false)
		return true;

	return GetSlotData()->IsEmpty();
}

UBaseDragDropOperation* USlotUI::GetSlotData()
{
	if (IsValid(DragDropOperation) == false)
	{
		TSubclassOf<UBaseDragDropOperation> OperationClass = GetDragDropOperationClass();
		if (IsValid(OperationClass) == false)
		{
			DEBUG_LOG("SlotUI::NativeOnDragDetected Error. DragDropOperationClass 정보가 없습니다. ");
			return nullptr;
		}

		DragDropOperation = Cast<UBaseDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(OperationClass));
		DragDropOperation->SetMaster(this);
		DragDropOperation->SetDragedSlotType(SlotType);
	}

	return DragDropOperation;
}

void USlotUI::SetItemData(FItemData& NewItemData)
{
	UBaseDragDropOperation* SlotData = GetSlotData();
	if (IsValid(SlotData) == true)
	{
		SlotData->SetItemData(NewItemData);
	}
	RefreshUI();
}

const FItemData& USlotUI::GetItemData()
{
	UBaseDragDropOperation* SlotData = GetSlotData();

	if (IsValid(SlotData) == true)
	{
		return SlotData->GetItemData();
	}

	return FItemData::EmptyItemData;
}

void USlotUI::SetSkillData(FSkillData NewSkillData)
{
	UBaseDragDropOperation* SlotData = GetSlotData();
	if (IsValid(SlotData) == true)
	{
		SlotData->SetSkillData(NewSkillData);
	}
	RefreshUI();
}

const FSkillData& USlotUI::GetSkillData()
{
	
	UBaseDragDropOperation* SlotData = GetSlotData();

	if (IsValid(SlotData) == true)
	{
		return SlotData->GetSkillData();
	}

	return FSkillData::EmptySkillData;
}

TSubclassOf<UDraggableWidget> USlotUI::GetDraggableWidgetClass(FString Name)
{
	if(Name.IsEmpty())
	{ 
		TSubclassOf<UDraggableWidget> RLRClass = GameInstance->GetDataManager()->GetWidgetClass<UDraggableWidget>(TEXT("WBP_DraggableWidget"));
		return RLRClass;
	}
	else
	{
		TSubclassOf<UDraggableWidget> RLRClass = GameInstance->GetDataManager()->GetWidgetClass<UDraggableWidget>(*Name);
		return RLRClass;
	}
}

TSubclassOf<UBaseDragDropOperation> USlotUI::GetDragDropOperationClass(FString Name)
{
	if (Name.IsEmpty())
	{
		TSubclassOf<UBaseDragDropOperation> RLRClass = GameInstance->GetDataManager()->GetWidgetClass<UBaseDragDropOperation>(TEXT("WBP_BaseDragDropOperation"));
		return RLRClass;
	}
	else
	{
		TSubclassOf<UBaseDragDropOperation> RLRClass = GameInstance->GetDataManager()->GetWidgetClass<UBaseDragDropOperation>(*Name);
		return RLRClass;
	}
}

UBaseDragDropOperation* USlotUI::CheckValidAndType(UDragDropOperation* InOperation, ESlotType DragType)
{
	UBaseDragDropOperation* Operation = Cast<UBaseDragDropOperation>(InOperation);
	if (IsValid(Operation) == false)
		return nullptr;
	if (IsValid(Operation->Master) == false)
		return nullptr;
	if (Operation->DragedSlotType != DragType)
		return nullptr;

	return Operation;
}

UBaseDragDropOperation* USlotUI::CheckValidAndType(UDragDropOperation* InOperation, ESlotType DragType, ESlotType DragType2)
{
	UBaseDragDropOperation* Operation = Cast<UBaseDragDropOperation>(InOperation);
	if (IsValid(Operation) == false)
		return nullptr;
	if (IsValid(Operation->Master) == false)
		return nullptr;
	if (Operation->DragedSlotType != DragType && Operation->DragedSlotType != DragType2)
		return nullptr;

	return Operation;
}

UTexture2D* USlotUI::GetDefaultSlotImage()
{
	if(IsValid(DefaultSlotImage) == true)
		return DefaultSlotImage;


	return GetGameManager()->GetDataManager()->GetResource("DefaultSlotImage").Texture;
}
