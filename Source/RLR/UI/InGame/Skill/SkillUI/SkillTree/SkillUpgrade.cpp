// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillTree/SkillUpgrade.h"

#include "Components/Button.h"

void USkillUpgrade::NativeConstruct()
{
	Super::NativeConstruct();

	SetUIType(EUIType::SKILL_UPGRADE);
	SetUITag(FGameplayTagManager::Get().UI_SkillUpgrade);

	CloseButton->OnClicked.AddUniqueDynamic(this, &USkillUpgrade::CloseUI);

}

void USkillUpgrade::RefreshUI()
{
	//스킬 데이터가 없으면 닫는다.
	TSharedPtr<FSkillData> skill = SkillData.Pin();
	if (*skill.Get() == FSkillData::EmptySkillData)
	{
		CloseUI();
		return;
	}


	/*
		현재 스킬 레벨 및 기타 정보
		필요한 재료 등등... 기획이 다 되면 다시 작업해주기
	
	*/
	
}

void USkillUpgrade::OpenUI()
{
	Super::OpenUI();
	SetVisibility(ESlateVisibility::Visible);
}

void USkillUpgrade::CloseUI()
{
	Super::CloseUI();
	SetVisibility(ESlateVisibility::Hidden);
}

void USkillUpgrade::SetSkillData(FSkillData& NewSkillData)
{
	TSharedPtr<FSkillData> skill = MakeShared<FSkillData>(NewSkillData);
	SkillData = skill.ToWeakPtr();

	RefreshUI();
}
