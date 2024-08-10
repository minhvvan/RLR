// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "GameplayTagsManager.h"
#include "SkillSetting.generated.h"

/**
 * 
 */

class USkillDetailInfo;
class UButton;
class UWidgetSwitcher;
class USkillTree;
class USkillSetting;
class USkillSettingQuickSlot;
class USkillSettingListSlot;
class UWrapBox;
class UUniformGridPanel;


UENUM(BlueprintType)
enum class SkillSetting_TabType : uint8
{
	NORMAL,
	UNIQUE,
	ULTIMATE,
	NONE,
};

UCLASS()
class RLR_API USkillSetting : public UBaseUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void RefreshUI() override;

	UFUNCTION()
	void OnClickedNormalSkillTab();
	UFUNCTION()
	void OnClickedUniqueSkillTab();
	UFUNCTION()
	void OnClickedUltimateSkillTab();

	void LoadQuickSlotData();
	void LoadSkillList();

	void SaveQuickSlotData();

	void ChangeTab(SkillSetting_TabType TabType);

public:

	/*
		binding
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> NormalSkillTabButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> UniqueSkillTabButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> UltimateSkillTabButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> SkillTabSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UWrapBox> NormalSkillWrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UWrapBox>	UniqueSkillWrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UWrapBox>	UltimateSkillWrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UUniformGridPanel>	SkillQuickSlotGridPanel;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USkillSettingListSlot> SkillSettingListSlotClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USkillSettingQuickSlot> SkillSettingQuickSlotClass;

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<USkillSettingQuickSlot>> SkillQuickSlotMap;
};
