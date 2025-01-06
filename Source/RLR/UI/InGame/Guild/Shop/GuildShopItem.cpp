// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/Shop/GuildShopItem.h"
#include "UI/InGame/Guild/Shop/GuildShopItemSlot.h"

#include "Components/Button.h"


void UGuildShopItem::SetItemData(const FItemData& NewItemData)
{
    ItemData = NewItemData;
    if (ItemSlot)
    {
        ItemSlot->SetItemData(ItemData);
    }
}

void UGuildShopItem::RefreshUI()
{
    if (ItemSlot)
    {
        ItemSlot->RefreshUI();
    }

    // 아이템 정보가 있다면 구매 버튼 활성화
    if (PurchaseButton)
    {
        if (ItemData != FItemData::EmptyItemData)
        {
            PurchaseButton->SetIsEnabled(true);
        }
    }
}