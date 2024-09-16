// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "UI/SlotUI.h"
#include "Structs/ItemStructs.h"
#include "GameManager/GameplayTagManager.h"
#include "ItemQuickSlot.generated.h"

/**
 * 
 */

 class UImage;
 class UTextBlock;

UCLASS()
class RLR_API UItemQuickSlot : public USlotUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void RefreshUI() override;
	virtual void Clear() override;

	virtual void UpdatedItemQuickSlot();

	void SetActionTag(FGameplayTag NewActionTag);

public:

	/*
		Bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UTextBlock> KeyBindingText;

public:

	UPROPERTY(EditAnywhere)
	FItemData SlotItemData;

	UPROPERTY()
	FGameplayTag ActionTag;
};
