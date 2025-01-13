// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/Shop/GuildPersonalShopUI.h"
#include "UI/InGame/Guild/Shop/GuildShopItem.h"

void UGuildPersonalShopUI::NativeConstruct()
{
}

/* 서버로 부터 길드 -> 개인 상점 아이템 정보 받아오기 */
void UGuildPersonalShopUI::SetGuildShopData(const TArray<FItemData>& ItemDataArray)
{
	for (int32 Index = 0; Index < ItemSlots.Num(); ++Index)
	{
		if (ItemDataArray.IsValidIndex(Index))
		{
			ItemSlots[Index]->SetItemData(ItemDataArray[Index]);
			ItemSlots[Index]->RefreshUI();
		}
		else
		{
			ItemSlots[Index]->SetItemData(FItemData::EmptyItemData);
			ItemSlots[Index]->RefreshUI();
		}
	}
}