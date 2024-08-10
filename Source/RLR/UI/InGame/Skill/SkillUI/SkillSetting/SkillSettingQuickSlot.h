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
	virtual void RefreshUI() override;

	void SetActionTag(FGameplayTag NewActionTag);
	void SetInputTag(FGameplayTag NewInputTag);
	void SetSkillData(FSkillData NewSkillData);
	virtual bool IsEmpty() override;



public:

	FGameplayTag ActionTag;
	FGameplayTag InputTag;
	FSkillData SkillData;
	
};
