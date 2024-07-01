// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SlotUI.h"
#include "UI/BaseDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


void USlotUI::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

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

FReply USlotUI::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

	FVector2D MousePos = InMouseEvent.GetScreenSpacePosition();
	DragOffset = InGeometry.AbsoluteToLocal(MousePos);

	FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	return ReplyResult.NativeReply;
}

void USlotUI::Clear()
{

}

bool USlotUI::IsEmpty()
{
	return true;
}

UBaseDragDropOperation* USlotUI::CheckValidAndType(UDragDropOperation* InOperation, EDragType DragType)
{
	UBaseDragDropOperation* Operation = Cast<UBaseDragDropOperation>(InOperation);
	if (IsValid(Operation) == false)
		return nullptr;
	if (IsValid(Operation->Master) == false)
		return nullptr;
	if (Operation->StartingDragType != DragType)
		return nullptr;

	return Operation;
}

UBaseDragDropOperation* USlotUI::CheckValidAndType(UDragDropOperation* InOperation, EDragType DragType, EDragType DragType2)
{
	UBaseDragDropOperation* Operation = Cast<UBaseDragDropOperation>(InOperation);
	if (IsValid(Operation) == false)
		return nullptr;
	if (IsValid(Operation->Master) == false)
		return nullptr;
	if (Operation->StartingDragType != DragType && Operation->StartingDragType != DragType2)
		return nullptr;

	return Operation;
}
