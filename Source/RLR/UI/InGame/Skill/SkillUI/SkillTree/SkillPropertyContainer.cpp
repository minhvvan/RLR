
// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InGame/Skill/SkillUI/SkillTree/SkillPropertyContainer.h"

#include "SkillPropertySlot.h"
#include "Components/Image.h"
#include "GameManager/DataManager.h"


void USkillPropertyContainer::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SkillPropertySlots.Add(SkillPropertySlot_1);
	SkillPropertySlots.Add(SkillPropertySlot_2);
	SkillPropertySlots.Add(SkillPropertySlot_3);
	SkillPropertySlots.Add(SkillPropertySlot_4);
	SkillPropertySlots.Add(SkillPropertySlot_5);
}

void USkillPropertyContainer::NativeConstruct()
{
	Super::NativeConstruct();
	bLearned = false;
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

	if (bLearned)
	{
		//TODO: 스킬별 속성 개수 만큼 UnLock
	}
	else
	{
		SetPropertiesUnlock(0);
	}
}

void USkillPropertyContainer::SetSkillData(FSkillData NewSkillData)
{
	SkillData = NewSkillData;
}

void USkillPropertyContainer::SetSkillLearned(bool Learned)
{
	bLearned = Learned;
}

void USkillPropertyContainer::SetPropertiesUnlock(int UnlockNum)
{
	if (SkillPropertySlots.Num() < UnlockNum) return;
	
	for (int i = 0 ; i < UnlockNum; i++)
	{
		SkillPropertySlots[i]->UnLock();
	}

	for (int i = UnlockNum ; i < SkillPropertySlots.Num(); i++)
	{
		SkillPropertySlots[i]->Lock();
	}
}
