// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCShopItemSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/TextBlock.h"
#include "Components/PanelWidget.h"
#include "Structs/ItemStructs.h"
#include "Structs/UtilStructs.h"
#include "UI/InGame/Shop/NPCPurchaseTab.h"
#include "UI/InGame/Shop/NPCSaleTab.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "RLR.h"

void UNPCShopItemSlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	UNPCShopItemSlot* itemSlot = Cast<UNPCShopItemSlot>(ListItemObject);

	if (itemSlot)
	{
		SetParent(itemSlot->GetParentUI());
		SetItemData(const_cast<FItemData&>(itemSlot->GetItemData()));
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
			if (ParentUI->IsA(UNPCPurchaseTab::StaticClass()))
			{
				Cast<UNPCPurchaseTab>(ParentUI)->OpenBundlePurchase(GetItemData());
			}
		}
		else
		{
			if (ParentUI->IsA(UNPCPurchaseTab::StaticClass()))
			{
				FItemData item(GetItemData());
				item.ITEM_VALUE = 1;
				Cast<UNPCPurchaseTab>(ParentUI)->AddToCart(item);
			}
			else if (ParentUI->IsA(UNPCSaleTab::StaticClass()))
			{
				Cast<UNPCSaleTab>(ParentUI)->RemoveFromCart(GetItemData());
				auto UIManager = GetUIManager();
				if (!UIManager) return result;
				UIManager->RemoveSaleItem(GetItemData());
				SetItemData(FItemData::EmptyItemData);
				RefreshUI();
			}
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
	if (itemData == FItemData::EmptyItemData)
	{
		SetIsEnabled(false);
		TxtItemName->SetVisibility(ESlateVisibility::Hidden);
		TxtItemAmount->SetVisibility(ESlateVisibility::Hidden);
		TxtPrice->SetVisibility(ESlateVisibility::Hidden);
		SlotImage->SetVisibility(ESlateVisibility::Hidden);
		ImgPrice->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		SetIsEnabled(true);
		TxtItemName->SetVisibility(ESlateVisibility::Visible);
		TxtPrice->SetVisibility(ESlateVisibility::Visible);
		SlotImage->SetVisibility(ESlateVisibility::Visible);
		ImgPrice->SetVisibility(ESlateVisibility::Visible);

		TxtItemName->SetText(itemData.NAME);
		TxtItemAmount->SetText(FText::AsNumber(itemData.ITEM_VALUE));
		TxtPrice->SetText(FText::AsNumber(itemData.SALE_PRICE));
		SlotImage->SetBrushFromTexture(itemData.ItemImage);

		//아이템 수량 표시
		if (!ParentUI) return;
		if (ParentUI->IsA(UNPCSaleTab::StaticClass())) SetItemAmountShow(true);
		else SetItemAmountShow(false);
	}
}

void UNPCShopItemSlot::SetParent(TObjectPtr<UBaseUI> parent)
{
	ParentUI = parent;
}

void UNPCShopItemSlot::SetItemAmountShow(bool bVisible)
{
	if(bVisible) TxtItemAmount->SetVisibility(ESlateVisibility::Visible);
	else TxtItemAmount->SetVisibility(ESlateVisibility::Hidden);
}