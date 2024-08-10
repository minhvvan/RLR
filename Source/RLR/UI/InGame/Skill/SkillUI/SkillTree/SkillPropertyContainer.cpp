
// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InGame/Skill/SkillUI/SkillTree/SkillPropertyContainer.h"


void USkillPropertyContainer::NativeConstruct()
{
	Super::NativeConstruct();

}

void USkillPropertyContainer::OpenUI()
{
	Super::OpenUI();
}


void USkillPropertyContainer::CloseUI()
{
	Super::CloseUI();

}

void USkillPropertyContainer::RefreshUI()
{
	Super::RefreshUI();

	if (SkillData == FSkillData::EmptySkillData)
	{
		CloseUI();
		return;
	}

	/*
		스킬 데이터에 스킬 속성이 생기면 추가로 작업해주기.
	*/
}

void USkillPropertyContainer::SetSkillData(FSkillData NewSkillData)
{
	SkillData = NewSkillData;
	RefreshUI();
}