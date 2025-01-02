// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "SkillUI.generated.h"

/**
 * 
 */

 class USkillDetailInfo;
 class UButton;
 class UWidgetSwitcher;
 class USkillTree;
 class USkillSetting;


UENUM(BlueprintType)
enum class SKillUI_TabType : uint8
{
	SKILL_TREE,
	SKILL_SETTING,
	NONE,
};


UCLASS()
class RLR_API USkillUI : public USubUI
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	virtual void Init();
	virtual void OpenUI() override;
	virtual void RefreshUI() override;
	
	UFUNCTION()
	void OnClickedSkillTreeTab();
	UFUNCTION()
	void OnClickedSkillSettingTab();
	void ChangeTab(SKillUI_TabType TabType);

	void UpdateSkillDetailInfo(const FSkillData& NewSkillData, bool bIsLearned) const;
	void ClearSkillDetailInfo();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USkillDetailInfo> SkillDetailInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> SkillTreeTabButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> SkillSettingTabButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> SkillWidgetSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USkillTree> SkillTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USkillSetting> SkillSetting;
};
