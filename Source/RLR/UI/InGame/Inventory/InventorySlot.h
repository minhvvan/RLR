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
	void			DisplayEquippedItems(bool IsEquiped = false);

	virtual void	OnClickedSlotButton() override;
	virtual void	OnHoveredSlotButton() override;
	virtual void	OnUnHoveredSlotButton() override;
	virtual void	Clear();

public:

	/*
		슬롯 이미지
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UImage> ItemRarityImage;


public:

	UPROPERTY(EditAnywhere)
	UInventoryUI* Inventory;
};
