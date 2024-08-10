// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillUI.h"
#include "SkillUI.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

#include "UI/InGame/Skill/SkillUI/SkillTree/SkillTree.h"
#include "UI/InGame/Skill/SkillUI/SkillTree/SkillPropertyContainer.h"
#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSetting.h"
#include "UI/InGame/Skill/SkillUI/SkillDetailInfo.h"

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

void USkillUI::OpenUI()
{
	Super::OpenUI();
	ClearSkillDetailInfo();
}

void USkillUI::RefreshUI()
{
	Super::RefreshUI();

	SkillTree->RefreshUI();
	SkillSetting->RefreshUI();
}

void USkillUI::OnClickedSkillTreeTab()
{
	ChangeTab(SKillUI_TabType::SKILL_TREE);
	SkillTree->RefreshUI();
}

void USkillUI::OnClickedSkillSettingTab()
{
	ChangeTab(SKillUI_TabType::SKILL_SETTING);
	SkillSetting->RefreshUI();
}

void USkillUI::ChangeTab(SKillUI_TabType TabType)
{
	SkillWidgetSwitcher->SetActiveWidgetIndex((int32)TabType); 
	RefreshUI();
}

void USkillUI::UpdateSkillDetailInfo(FSkillData NewSkillData)
{
	SkillDetailInfo->SetSkillData(NewSkillData);

	if (NewSkillData == FSkillData::EmptySkillData)
	{
		SkillTree->SkillPropertyContainer->CloseUI();
		return;
	}

	//고유기만 스킬 프로퍼티를 보여준다.
	if (NewSkillData.SkillGroup == ESkillGroup::UNIQUE)
	{
		SkillTree->SkillPropertyContainer->SetSkillData(NewSkillData);
		SkillTree->SkillPropertyContainer->OpenUI();
	}
	else
	{
		SkillTree->SkillPropertyContainer->CloseUI();
	}


}

void USkillUI::ClearSkillDetailInfo()
{
	SkillDetailInfo->SetVisibility(ESlateVisibility::Hidden);

}


