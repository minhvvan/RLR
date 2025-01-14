// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlotUI.h"
#include "GameManager/RLRStruct.h"
#include "SkillTreeSlot.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API USkillTreeSlot : public USlotUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;


	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void RefreshUI() override;

	virtual void SetLearned(bool Value);
	virtual bool GetLearned() { return IsLearned; }

private:
	UPROPERTY()
	bool IsLearned = false;
};
