// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "Structs/ItemStructs.h"
#include "GuildShopUI.generated.h"

class UGuildShopItem;
/**
 * 길드 상점
 */
UCLASS()
class RLR_API UGuildShopUI : public USubUI
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;
	void SetGuildShopData(const TArray<FItemData>& ItemDataArray);

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TArray<TObjectPtr<UGuildShopItem>> ShopItems;
};
