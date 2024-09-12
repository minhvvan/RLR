// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlotUI.h"
#include "GameplayTagsManager.h"
#include "SkillSettingQuickSlot.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API USkillSettingQuickSlot : public USlotUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	//드래그 드랍
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void RefreshUI() override;

	void SetActionTag(FGameplayTag NewActionTag);
	void SetInputTag(FGameplayTag NewInputTag);
	
public:

	FGameplayTag ActionTag;
	FGameplayTag InputTag;
};
