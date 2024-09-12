// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlotUI.h"
#include "SkillSettingListSlot.generated.h"

/**
 * 
 */

 class UTextBlock;

UCLASS()
class RLR_API USkillSettingListSlot : public USlotUI
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	//드래그 드랍
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void RefreshUI() override;
	virtual void SetEquipped(bool Value);

public:

	/*
		Binding
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> EquipStateText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillLevelText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillNameText;



private:

	UPROPERTY()
	bool IsEquipped = false;

};
