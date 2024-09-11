// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "NPCSaleTab.generated.h"

class UTileView;
class UTextBlock;
class UButton;
class UCanvasPanel;
class UNPCShopItemSlot;

UCLASS()
class RLR_API UNPCSaleTab : public UBaseUI
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Canvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTileView> TVItem;

	//payment
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtSellPrice;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtSafe;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> BtnSell;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> BtnEmpty;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void AddToCart(const FItemData& item);
	void RemoveFromCart(const FItemData& item);

protected:
	UFUNCTION()
	void OnSellClicked();

	UFUNCTION()
	void OnEmptyClicked();

	void UpdatePage();
	UNPCShopItemSlot* GetItemSlotWidget(int idx);
	void UpdatePrice();

	TArray<FItemData> Cart;
	int SellPrice = 0;
	const int MaxCartNum = 12;
};
