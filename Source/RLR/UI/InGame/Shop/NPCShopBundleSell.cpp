#include "NPCShopBundleSell.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCShopBundleSell.h"

#include "Components/EditableText.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "GameManager/GameManager.h"
#include "GameManager/InventoryManager.h"

void UNPCShopBundleSell::NativeConstruct()
{
	BtnConfirm->OnClicked.AddUniqueDynamic(this, &UNPCShopBundleSell::OnConfirmClicked);
	BtnCancel->OnClicked.AddUniqueDynamic(this, &UNPCShopBundleSell::OnCancelClicked);
	BtnIncrease->OnClicked.AddUniqueDynamic(this, &UNPCShopBundleSell::OnIncreaseClicked);
	BtnDecrease->OnClicked.AddUniqueDynamic(this, &UNPCShopBundleSell::OnDecreaseClicked);
}

void UNPCShopBundleSell::OnConfirmClicked()
{
	OnConfirmSell.Broadcast(Item, slotIndex);
	RemoveFromParent();
}

void UNPCShopBundleSell::OnCancelClicked()
{
	RemoveFromParent();
}

void UNPCShopBundleSell::OnIncreaseClicked()
{
	int32 itemQuantity = Item.ITEM_QUANTITY;
	Item.ITEM_QUANTITY++;
	if(GameInstance->GetInventoryManager()->GetItem(slotIndex).ITEM_QUANTITY < Item.ITEM_QUANTITY) 
	{
		Item.ITEM_QUANTITY = itemQuantity;
		return;
	}
	UpdateAmountText();
}

void UNPCShopBundleSell::OnDecreaseClicked()
{
	if (Item.ITEM_QUANTITY == 1) return;
	Item.ITEM_QUANTITY--;
	UpdateAmountText();
}

void UNPCShopBundleSell::UpdateAmountText()
{
	EdtAmount->SetText(FText::AsNumber(Item.ITEM_QUANTITY));
}

void UNPCShopBundleSell::SetSlotIndex(int32 NewSlotIndex)
{
	slotIndex = NewSlotIndex;
}

void UNPCShopBundleSell::SetItemData(const FItemData& item)
{
	Item = item;
	ImgItem->SetBrushFromTexture(Item.GetItemResource().ItemImage);
	UpdateAmountText();
}
