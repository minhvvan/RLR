// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillUI.h"
#include "SkillUI.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "UI/InGame/Skill/SkillUI/SkillTree/SkillTree.h"
#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSetting.h"

void USkillUI::NativeConstruct()
{
	Super::NativeConstruct();

	SetUIType(EUIType::SKILL);
	SetUITag(FGameplayTagManager::Get().UI_Skill);


	SkillTreeTabButton->OnClicked.AddUniqueDynamic(this, &USkillUI::OnClickedSkillTreeTab);
	SkillSettingTabButton->OnClicked.AddUniqueDynamic(this, &USkillUI::OnClickedSkillSettingTab);

}

void USkillUI::Init()
{

}

void USkillUI::RefreshUI()
{
	Super::RefreshUI();


}

void USkillUI::OnClickedSkillTreeTab()
{
	ChangeSkillTab(SKillUI_TabType::SKILL_TREE);
	SkillTree->RefreshUI();
}

void USkillUI::OnClickedSkillSettingTab()
{
	ChangeSkillTab(SKillUI_TabType::SKILL_SETTING);
	SkillSetting->RefreshUI();
}

void USkillUI::ChangeSkillTab(SKillUI_TabType TabType)
{
	SkillWidgetSwitcher->SetActiveWidgetIndex((int32)TabType); 
	RefreshUI();
}


