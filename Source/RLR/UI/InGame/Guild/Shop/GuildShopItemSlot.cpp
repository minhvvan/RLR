// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/Shop/GuildShopItemSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "Structs/ItemStructs.h"
#include "RLR.h"

void UGuildShopItemSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (ItemData == FItemData::EmptyItemData)
        return;

    UUIManager* UIManager = GetUIManager();
    if (UIManager == nullptr) return;

    UMainUI* mainUI = UIManager->GetPage<UMainUI>(UIManager->GetActivePageTag());
    if (mainUI == nullptr) return;

    mainUI->OpenSubUINearTargetSlot(this, RLRTAG.UI_ItemInfomation);
}

void UGuildShopItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    auto UIManager = GetUIManager();

    if (UIManager)
    {
        UIManager->CloseSubUI(RLRTAG.UI_ItemInfomation);
    }
}

void UGuildShopItemSlot::RefreshUI()
{
    auto itemData = GetItemData();
    FItemResource itemResourceData = GetItemResourceData();
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
        TxtItemAmount->SetText(FText::AsNumber(itemData.ITEM_QUANTITY));
        TxtPrice->SetText(FText::AsNumber(itemData.SALE_PRICE));
        SlotImage->SetBrushFromTexture(itemResourceData.ItemImage);

        //아이템 수량 표시
        SetItemAmountShow(true);
    }
}

void UGuildShopItemSlot::SetItemAmountShow(bool bVisible)
{
    if (bVisible)
        TxtItemAmount->SetVisibility(ESlateVisibility::Visible);
    else
        TxtItemAmount->SetVisibility(ESlateVisibility::Hidden);
}