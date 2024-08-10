// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SlotUI.h"
#include "UI/BaseDragDropOperation.h"

#include "Components/Button.h"
#include "Components/Image.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"


void USlotUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotButton)
	{
		SlotButton->OnClicked.AddUniqueDynamic(this, &USlotUI::OnClickedSlotButton);
		SlotButton->OnHovered.AddUniqueDynamic(this, &USlotUI::OnHoveredSlotButton);
		SlotButton->OnUnhovered.AddUniqueDynamic(this, &USlotUI::OnUnHoveredSlotButton);
	}

}

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
		DEBUG_LOG("Set Slot Image Error. New Image is Null");
		return;
	}

	SlotImage->SetBrushFromTexture(NewImage);
}

void USlotUI::Clear()
{
	SlotImage->SetBrushFromTexture(DefaultSlotImage);
}

bool USlotUI::IsEmpty()
{
	/*
		Empty의 유무를 어떻게 판단해줄까?
			그냥 상속 받는 슬롯들마다 서로 다르게 설정할까?
			아니면 공통된 기준을 만들까?
	*/
	if(SlotImage->GetBrush().GetResourceName() == DefaultSlotImage->GetName())
		return true;

	return false;
}

UBaseDragDropOperation* USlotUI::CheckValidAndType(UDragDropOperation* InOperation, EDragType DragType)
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

UBaseDragDropOperation* USlotUI::CheckValidAndType(UDragDropOperation* InOperation, EDragType DragType, EDragType DragType2)
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
