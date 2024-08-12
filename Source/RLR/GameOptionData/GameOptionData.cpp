// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOptionData/GameOptionData.h"
#include "GameManager/GameplayTagManager.h"

const FString UGameOptionData::SlotName =  FString(TEXT("GameOptionData"));

void UGameOptionData::Init()
{

	ChatOption.Init();
	SkillQuickSlotOption.Init();

}

FSkillQuickSlotOption& UGameOptionData::GetSkillQuickSlotOption()
{
	if(SkillQuickSlotOption.SkillQuickSlotList.Num() == 0)
		SkillQuickSlotOption.Init();

	return SkillQuickSlotOption;
}

void FChatOption::Init()
{
	bVisibleChatOption.Add(EChatType::General, true);
	bVisibleChatOption.Add(EChatType::Whisper, true);
	bVisibleChatOption.Add(EChatType::Country, true);
	bVisibleChatOption.Add(EChatType::World, true);
	bVisibleChatOption.Add(EChatType::Guild, true);
	bVisibleChatOption.Add(EChatType::Raid, true);
	bVisibleChatOption.Add(EChatType::Party, true);
	bVisibleChatOption.Add(EChatType::Continent, true);
	bVisibleChatOption.Add(EChatType::Nearby, true);
}


void FSkillQuickSlotOption::Init()
{

	SkillQuickSlotList.Add(FGameplayTagManager::Get().Action_Skill_1_Anim, -1);
	SkillQuickSlotList.Add(FGameplayTagManager::Get().Action_Skill_2_Anim, -1);
	SkillQuickSlotList.Add(FGameplayTagManager::Get().Action_Skill_3_Anim, -1);
	SkillQuickSlotList.Add(FGameplayTagManager::Get().Action_Skill_4_Anim, -1);
	SkillQuickSlotList.Add(FGameplayTagManager::Get().Action_Skill_5_Anim, -1);
	SkillQuickSlotList.Add(FGameplayTagManager::Get().Action_Skill_6_Anim, -1);
	SkillQuickSlotList.Add(FGameplayTagManager::Get().Action_Skill_7_Anim, -1);
	SkillQuickSlotList.Add(FGameplayTagManager::Get().Action_Skill_8_Anim, -1);
}

bool FSkillQuickSlotOption::IsEquippedSkill(int32 Id)
{

	for (TTuple<FGameplayTag, int32> Element : SkillQuickSlotList)
	{
		int32 Skill_ID = Element.Value;

		if(Skill_ID == Id)
			return true;
	}

	return false;
}

