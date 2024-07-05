// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "StatusDisplay.generated.h"

/**
 * 
 */

 class UGridPanel;
 class UProgressGlobe;
 class USkillQuickSlotContainer;
 class UItemQuickSlotContainer;

UCLASS()
class RLR_API UStatusDisplay : public UBaseUI
{
	GENERATED_BODY()
	

public:

	//Bind Widget

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UProgressGlobe> HPGlobe;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UProgressGlobe> MPGlobe;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<USkillQuickSlotContainer> SkillQuickSlotContainer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UItemQuickSlotContainer> ItemQuickSlotContainer;

};
