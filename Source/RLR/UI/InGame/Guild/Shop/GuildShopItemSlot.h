// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlotUI.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "GuildShopItemSlot.generated.h"

class UTextBlock;
class UImage;
/**
 * 길드 상점 아이템 슬롯 (아이템 이미지, 아이템 개수, 아이템 정보)
 */
UCLASS()
class RLR_API UGuildShopItemSlot : public USlotUI, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
    virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

    void RefreshUI();
    void SetItemAmountShow(bool bVisible);

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* TxtItemName;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TxtItemAmount;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TxtPrice;

    UPROPERTY(meta = (BindWidget))
    UImage* ImgPrice;

private:
    FItemData ItemData;
};
