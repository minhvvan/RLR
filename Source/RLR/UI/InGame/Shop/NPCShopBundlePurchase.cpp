// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCShopBundlePurchase.h"
#include "Components/Button.h"

void UNPCShopBundlePurchase::NativeConstruct()
{
	BtnConfirm->OnClicked.AddDynamic(this, &UNPCShopBundlePurchase::OnConfirmClicked);
	BtnCancel->OnClicked.AddDynamic(this, &UNPCShopBundlePurchase::OnCancelClicked);
}

void UNPCShopBundlePurchase::OnConfirmClicked()
{
	//TODO: Add To Cart
}

void UNPCShopBundlePurchase::OnCancelClicked()
{
	RemoveFromParent();
}

void UNPCShopBundlePurchase::SetItemData(const FItemData& item)
{
	//TODO: 아이템 정보 표시
}
