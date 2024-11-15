// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameManager/DataManager.h"
#include "UI/BaseUI.h"
#include "UI/SlotUI.h"
#include "InventorySlot.generated.h"

/**
 * 
 */

 class UImage;
 class UButton;
 class UInventoryUI;
 class UTextBlock;

UCLASS()
class RLR_API UInventorySlot : public USlotUI
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	//virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void RefreshUI() override;

	UFUNCTION(BlueprintImplementableEvent)
	void DisplayEquippedItems(bool IsEquiped = false);

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void Clear();
	void OnSelected();
	void CancelSelected();

	virtual void SetIsEnabled(bool bInIsEnabled) override;

public:

	/*
		슬롯 이미지
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UImage> ItemRarityImage;

	/*
		아이템 이미지 구하기 전까지 그냥 아이템 이름을 출력하려고 만든 녀석.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;

public:
	UPROPERTY(EditAnywhere)
	UInventoryUI* Inventory;

protected:
	UPROPERTY(EditAnywhere, Category = Color)
	TMap<bool, FLinearColor> SlotColors;
};
