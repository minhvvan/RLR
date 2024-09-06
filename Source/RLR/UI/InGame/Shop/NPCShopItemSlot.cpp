// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCShopItemSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/TextBlock.h"
#include "Components/PanelWidget.h"
#include "Structs/ItemStructs.h"
#include "UI/InGame/Shop/NPCPurchaseTab.h"
#include "RLR.h"

void UNPCShopItemSlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	UNPCShopItemSlot* itemSlot = Cast<UNPCShopItemSlot>(ListItemObject);

	if (itemSlot)
	{
		SetItemData(const_cast<FItemData&>(itemSlot->GetItemData()));
		SetParent(itemSlot->GetParentUI());
		RefreshUI();
	}
}

FReply UNPCShopItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		if (InMouseEvent.IsLeftShiftDown())
		{
			//TODO: 개수 선택 UI POP
			RLR_LOG(LogRLR, Log, TEXT("right shift + click"));
			if (ParentUI) ParentUI->OpenBundlePurchase(GetItemData());
		}
		else
		{
			RLR_LOG(LogRLR, Log, TEXT("right click"));
			FItemData item(GetItemData());
			item.ITEM_VALUE = 1;
			if (ParentUI) ParentUI->AddToCart(item);
		}
	}

	return result;
}

void UNPCShopItemSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//TODO: Show Item Info
	RLR_LOG(LogRLR, Log, TEXT("OnHoveredSlotButton"));
}

void UNPCShopItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	//TODO: Show Off Item Info
	RLR_LOG(LogRLR, Log, TEXT("OnUnHoveredSlotButton"));
}

void UNPCShopItemSlot::RefreshUI()
{
	auto itemData = GetItemData();
	TxtItemName->SetText(itemData.NAME);
	TxtPrice->SetText(FText::AsNumber(itemData.SALE_PRICE));
	SlotImage->SetBrushFromTexture(itemData.ItemImage);
}

void UNPCShopItemSlot::SetParent(TObjectPtr<UNPCPurchaseTab> Parent)
{
	ParentUI = Parent;
}
