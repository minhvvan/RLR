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
class USkillSettingQuickSlotContainer;
class USkillSettingListSlot;
class USkillSettingListSlotContainer;
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
	virtual void Init() override;
	virtual void RefreshUI() override;
	virtual void Clear() override;
	void		 ClearSkillList();
	void		 ClearQuickSlot();

	void LoadQuickSlotData();
	void LoadSkillList();

	void ReqeustSkillQuickSlotChange();
	void SaveQuickSlotData();
	void ApplyQuickSlotSetting();

	UFUNCTION()
	void UpdatedSkillManager();

	void ChangeTab(SkillSetting_TabType TabType);


	UFUNCTION()
	void OnClickedNormalSkillTab();
	UFUNCTION()
	void OnClickedUniqueSkillTab();
	UFUNCTION()
	void OnClickedUltimateSkillTab();

	UFUNCTION()
	void OnClickedConfirmButton();
	UFUNCTION()
	void OnClickedCancelButton();

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
	TObjectPtr<UButton> ConfirmButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> CancelButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> SkillTabSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<USkillSettingListSlotContainer>	NormalSkillWrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<USkillSettingListSlotContainer>	UniqueSkillWrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<USkillSettingListSlotContainer>	UltimateSkillWrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<USkillSettingQuickSlotContainer>	SkillQuickSlotGridPanel;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 QuickSlotMaxColunm = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillListMaxColunm = 30;
};
