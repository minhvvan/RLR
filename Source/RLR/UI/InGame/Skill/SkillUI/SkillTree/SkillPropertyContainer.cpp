
// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InGame/Skill/SkillUI/SkillTree/SkillPropertyContainer.h"
#include "Components/Image.h"
#include "GameManager/DataManager.h"


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

	auto actionResource = GetDataManager()->GetActionResource(SkillData.SkillSeq);
	ImgSkill->SetBrushFromTexture(actionResource.ActionImage);
}

void USkillPropertyContainer::SetSkillData(FSkillData NewSkillData)
{
	SkillData = NewSkillData;
	RefreshUI();
}