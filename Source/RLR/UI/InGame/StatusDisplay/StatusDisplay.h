// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager/RLRStruct.h"
#include "UI/BaseUI.h"
#include "StatusDisplay.generated.h"

/**
 * 
 */

 class UGridPanel;
 class UProgressGlobe;
 class USkillQuickSlotContainer;
 class UItemQuickSlotContainer;
 class UExpProgressBar;

UCLASS()
class RLR_API UStatusDisplay : public UBaseUI
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UExpProgressBar> ExpProgressBar;


public:
	void UpdateTotalStat(const FTotalStatus& NewTotalStatus);

	void UpdateHpGlobe(float NewPercent);
	void UpdateMpGlobe(float NewPercent);
	void UpdateExp(float NewPercent);
};
