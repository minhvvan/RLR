// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UniformGridPanel.h"
#include "GameplayTagsManager.h"
#include "SkillSettingQuickSlotContainer.generated.h"

/**
 * 
 */


 class USkillSettingQuickSlot;

UCLASS()
class RLR_API USkillSettingQuickSlotContainer : public UUniformGridPanel
{
	GENERATED_BODY()

public:

	void Init();
	virtual void RefreshUI();
	virtual void Clear();

public:
	UPROPERTY()
	TMap<FGameplayTag, USkillSettingQuickSlot*> QuickSlotMap;
	
};
