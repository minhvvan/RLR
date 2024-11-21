// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCShopBundlePurchase.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/Image.h"

void UNPCShopBundlePurchase::NativeConstruct()
{
	BtnConfirm->OnClicked.AddUniqueDynamic(this, &UNPCShopBundlePurchase::OnConfirmClicked);
	BtnCancel->OnClicked.AddUniqueDynamic(this, &UNPCShopBundlePurchase::OnCancelClicked);
	BtnIncrease->OnClicked.AddUniqueDynamic(this, &UNPCShopBundlePurchase::OnIncreaseClicked);
	BtnDecrease->OnClicked.AddUniqueDynamic(this, &UNPCShopBundlePurchase::OnDecreaseClicked);
}

void UNPCShopBundlePurchase::OnConfirmClicked()
{
	OnConfirmPurchase.Broadcast(Item);
	RemoveFromParent();
}

void UNPCShopBundlePurchase::OnCancelClicked()
{
	RemoveFromParent();
}

void UNPCShopBundlePurchase::OnIncreaseClicked()
{
	Item.ITEM_QUANTITY++;
	UpdateAmountText();
}

void UNPCShopBundlePurchase::OnDecreaseClicked()
{
	if (Item.ITEM_QUANTITY == 1) return;
	Item.ITEM_QUANTITY--;
	UpdateAmountText();
}

void UNPCShopBundlePurchase::UpdateAmountText()
{
	EdtAmount->SetText(FText::AsNumber(Item.ITEM_QUANTITY));
}

void UNPCShopBundlePurchase::SetItemData(const FItemData& item)
{
	Item = item;
	ImgItem->SetBrushFromTexture(Item.GetItemResource().ItemImage);
	UpdateAmountText();
}
