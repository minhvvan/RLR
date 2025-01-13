// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ItemStructs.h"
#include "GuildShopItem.generated.h"

class UButton;
class UGuildShopItemSlot;
/**
 * 길드 상점의 각 아이템 (아이템 슬롯 + 구매 버튼)
 */
UCLASS()
class RLR_API UGuildShopItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetItemData(const FItemData& NewItemData);
	void RefreshUI();

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UGuildShopItemSlot> ItemSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PurchaseButton;

private:
	FItemData ItemData;
};
