// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCCartSlot.h"

void UNPCCartSlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	RefreshUI();
}

void UNPCCartSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
}

bool UNPCCartSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return false;
}

void UNPCCartSlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
}

void UNPCCartSlot::OnClickedSlotButton()
{
}

void UNPCCartSlot::OnHoveredSlotButton()
{
}

void UNPCCartSlot::OnUnHoveredSlotButton()
{
}
