// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "Structs/ObjectStructs.h"
#include "NPCShopUI.generated.h"

enum TabIndex
{
	EPurchase,
	ESale
};

class UButton;
class UWidgetSwitcher;
class UCanvasPanel;
struct FNPCShop;

UCLASS()
class RLR_API UNPCShopUI : public USubUI
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Canvas;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UButton> BtnPurchase;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> BtnSale;	
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> TabSwitcher;	

public:
	virtual void NativeConstruct() override;

	void SetItemData(const TArray<FItemData>& Items);
	void SetShopData(const FNPCShop& Data);

	FNPCShop& GetShopData();

	UPanelSlot* AddChild(UUserWidget* Child);

	UFUNCTION()
	void AddSaleItem(const FItemData& Item);

protected:
	UFUNCTION()
	void OnPurchaseClicked();

	UFUNCTION()
	void OnSaleClicked();

protected:
	TSharedPtr<TArray<FItemData>> ItemData;
	FNPCShop NPCShopData;
};
