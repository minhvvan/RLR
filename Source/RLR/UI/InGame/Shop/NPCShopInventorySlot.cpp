// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCShopInventorySlot.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "Structs/ItemStructs.h"
#include "Components/Button.h"
#include "RLR.h"

FReply UNPCShopInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = UUserWidget::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		auto UIManager = GameInstance->GetUIManager();
		if (!UIManager) return result;

		UIManager->AddSaleItem(GetItemData());
		SetIsEnabled(false);
	}

	return result;
}

void UNPCShopInventorySlot::RefreshUI()
{
	Super::RefreshUI();

	//TODO: 판매 가능 여부에 따라 변경 필요
	if(!GetIsEnabled()) SetIsEnabled(true);
}

void UNPCShopInventorySlot::CancelSale()
{
	SetIsEnabled(true);
}
