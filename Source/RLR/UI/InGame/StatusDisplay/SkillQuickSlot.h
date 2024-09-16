// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlotUI.h"
#include "GameOptionData/GameOptionData.h"
#include "SkillQuickSlot.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class RLR_API USkillQuickSlot : public USlotUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void RefreshUI() override;
	virtual void Clear() override;
	void UpdatedSkillQuickSlot();

	void SetActionTag(FGameplayTag NewActionTag);
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UTextBlock> KeyBindingText;

	UPROPERTY()
	FGameplayTag ActionTag;
};
