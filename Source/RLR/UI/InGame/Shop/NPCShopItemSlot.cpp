// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCShopItemSlot.h"

void UNPCShopItemSlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	RefreshUI();
}

void UNPCShopItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
}

bool UNPCShopItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return false;
}

void UNPCShopItemSlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
}

void UNPCShopItemSlot::OnClickedSlotButton()
{
}

void UNPCShopItemSlot::OnHoveredSlotButton()
{
}

void UNPCShopItemSlot::OnUnHoveredSlotButton()
{
}
