// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/Shop/GuildShopUI.h"
#include "UI/InGame/Guild/Shop/GuildShopItem.h"

void UGuildShopUI::NativeConstruct()
{
}

/* 서버로 부터 길드 -> 길드 상점 아이템 정보 받아오기 */
void UGuildShopUI::SetGuildShopData(const TArray<FItemData>& ItemDataArray)
{
	for (int32 Index = 0; Index < ShopItems.Num(); ++Index)
	{
		if (ItemDataArray.IsValidIndex(Index))
		{
			ShopItems[Index]->SetItemData(ItemDataArray[Index]);
			ShopItems[Index]->RefreshUI();
		}
		else
		{
			ShopItems[Index]->SetItemData(FItemData::EmptyItemData);
			ShopItems[Index]->RefreshUI();
		}
	}
}