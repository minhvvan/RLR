// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCCartSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Structs/ItemStructs.h"

void UNPCCartSlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	SetItemData(Cast<UNPCCartSlot>(ListItemObject)->GetItemData());
}

FReply UNPCCartSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (GetItemData() == FItemData::EmptyItemData) return result;
	GetListItem<UNPCCartSlot>()->OnCartClicked.Broadcast(GetItemData());
	return result;
}

void UNPCCartSlot::RefreshUI()
{
	auto itemData = GetItemData();
	FItemResource itemResourceData = GetItemResourceData();
	SetSlotImage(itemResourceData.ItemImage);
	TxtItemAmount->SetText(FText::AsNumber(itemData.ITEM_VALUE));
}