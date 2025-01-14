// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillTree/SkillPropertySlot.h"

#include "Components/Image.h"

void USkillPropertySlot::SetPropertyImage()
{
	//TODO: 속성 이미지 세팅 필요
}

void USkillPropertySlot::UnLock() const
{
	SkillLockImage->SetVisibility(ESlateVisibility::Hidden);
}

void USkillPropertySlot::Lock() const
{
	SkillLockImage->SetVisibility(ESlateVisibility::Visible);
}
