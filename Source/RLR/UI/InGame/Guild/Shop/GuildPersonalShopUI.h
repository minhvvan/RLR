// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ItemStructs.h"
#include "GuildPersonalShopUI.generated.h"

class UGuildShopItem;
/**
 * 길드 개인 상점
 */
UCLASS()
class RLR_API UGuildPersonalShopUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void SetGuildShopData(const TArray<FItemData>& ItemDataArray);


public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TArray<TObjectPtr<UGuildShopItem>> ItemSlots;
};
