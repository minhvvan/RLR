// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCShopItemSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/TextBlock.h"
#include "Components/PanelWidget.h"
#include "Structs/ItemStructs.h"
#include "Structs/UtilStructs.h"
#include "UI/InGame/Shop/NPCPurchaseTab.h"
#include "RLR.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"

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
			if (ParentUI) ParentUI->OpenBundlePurchase(GetItemData());
		}
		else
		{
			FItemData item(GetItemData());
			item.ITEM_VALUE = 1;
			if (ParentUI) ParentUI->AddToCart(item);
		}
	}

	return result;
}

void UNPCShopItemSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto UIMananger = GetUIManager();
	UIMananger->OpenSubUINearTargetSlot(this, EUIType::ITEMINFOMATION);
}

void UNPCShopItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	auto UIMananger = GetUIManager();
	UIMananger->CloseSubUI(EUIType::ITEMINFOMATION);
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
