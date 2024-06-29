// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "UI/SlotUI.h"
#include "ItemQuickSlot.generated.h"

/**
 * 
 */

 class UImage;

UCLASS()
class RLR_API UItemQuickSlot : public USlotUI
{
	GENERATED_BODY()

public:

	virtual void	NativeConstruct() override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void Clear() override;

	virtual bool IsEmpty() {return SlotItemData.ITEM_ID == -1;}

	UFUNCTION(BlueprintCallable)
	void				SetItemData(FItemData ItemData);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FItemData	GetItemData(){return SlotItemData;};



public:

	UPROPERTY(EditAnywhere)
	FItemData SlotItemData;
};
