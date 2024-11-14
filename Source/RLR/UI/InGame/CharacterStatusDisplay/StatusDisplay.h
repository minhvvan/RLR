// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager/RLRStruct.h"
#include "UI/SubUI.h"
#include "GameManager/GameplayTagManager.h"
#include "StatusDisplay.generated.h"

/**
 * 
 */

 class UGridPanel;
 class UProgressGlobe;
 class USkillQuickSlotContainer;
 class UItemQuickSlotContainer;
 class UExpProgressBar;
 class USkillQuickSlot;
 class UItemQuickSlot;

UCLASS()
class RLR_API UStatusDisplay : public USubUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void Init();
	virtual void RefreshUI() override;

	UFUNCTION()
	void SaveItemQuickSlotData();
	void LoadSkillQuickSlotData();
	void LoadItemQuickSlotData();

public:
	void UpdateTotalStat(const FTotalStatus& NewTotalStatus);

	void UpdateHpGlobe(float NewPercent);
	void UpdateMpGlobe(float NewPercent);
	void UpdateLevel(int32 NewLevel);
	void UpdateExp(int32 NewExp);

	UFUNCTION()
	void UpdateSkillQuickSlot(FGameplayTag ActionTag);
	UFUNCTION()
	void UpdateItemQuickSlot(FGameplayTag ActionTag);


	USkillQuickSlot*	GetSkillQuickSlot(FGameplayTag ActionTag);
	UItemQuickSlot*		GetItemQuickSlot(FGameplayTag ActionTag);

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
};
