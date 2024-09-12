// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCShopBundlePurchase.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/Image.h"

void UNPCShopBundlePurchase::NativeConstruct()
{
	BtnConfirm->OnClicked.AddDynamic(this, &UNPCShopBundlePurchase::OnConfirmClicked);
	BtnCancel->OnClicked.AddDynamic(this, &UNPCShopBundlePurchase::OnCancelClicked);
	BtnIncrease->OnClicked.AddDynamic(this, &UNPCShopBundlePurchase::OnIncreaseClicked);
	BtnDecrease->OnClicked.AddDynamic(this, &UNPCShopBundlePurchase::OnDecreaseClicked);
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
	Item.ITEM_VALUE++;
	UpdateAmountText();
}

void UNPCShopBundlePurchase::OnDecreaseClicked()
{
	if (Item.ITEM_VALUE == 1) return;
	Item.ITEM_VALUE--;
	UpdateAmountText();
}

void UNPCShopBundlePurchase::UpdateAmountText()
{
	EdtAmount->SetText(FText::AsNumber(Item.ITEM_VALUE));
}

void UNPCShopBundlePurchase::SetItemData(const FItemData& item)
{
	Item = item;
	ImgItem->SetBrushFromTexture(Item.ItemImage);
	UpdateAmountText();
}
