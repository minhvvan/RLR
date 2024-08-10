// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingQuickSlot.h"

void USkillSettingQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();

}

void USkillSettingQuickSlot::RefreshUI()
{
	Super::RefreshUI();

	if (SkillData == FSkillData::EmptySkillData)
	{
		SetSlotImage(DefaultSlotImage);
		return;
	}


	SetSlotImage(SkillData.SkillImage);
}

void USkillSettingQuickSlot::SetActionTag(FGameplayTag NewActionTag)
{

	ActionTag = NewActionTag;

}

void USkillSettingQuickSlot::SetInputTag(FGameplayTag NewInputTag)
{

	InputTag = NewInputTag;

}

void USkillSettingQuickSlot::SetSkillData(FSkillData NewSkillData)
{
	SkillData = NewSkillData;
}

bool USkillSettingQuickSlot::IsEmpty()
{
	if(SkillData == FSkillData::EmptySkillData)
		return true;

	return false;
}
