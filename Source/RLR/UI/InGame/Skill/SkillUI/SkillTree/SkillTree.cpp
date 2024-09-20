// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillTree/SkillTree.h"
#include "UI/InGame/Skill/SkillUI/SkillTree/SkillTreeSlot.h"
#include "UI/InGame/Skill/SkillUI/SkillTree/SkillPropertyContainer.h"
#include "UI/InGame/Skill/SkillUI/SkillTree/SkillPropertySlot.h"
#include "UI/InGame/Skill/SkillUI/SkillTree/SkillTreeSlotContainer.h"


#include "ActionSystem/StatSet/StatSetPlayer.h"

#include "GameManager/RLRStruct.h"
#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/PlayerManager.h"

#include "Components/WrapBox.h"
#include "Components/TextBlock.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void USkillTree::NativeConstruct()
{
	Super::NativeConstruct();
	SetUIType(EUIType::SKILL_TREE);
}

void USkillTree::Init()
{
	Super::Init();

	NormalSkillWrapBox->Init();
	UniqueSkillWrapBox->Init();
	UltimateSkillWrapBox->Init();
}

void USkillTree::RefreshUI()
{
	Super::RefreshUI();
	LoadSkillList();
}

void USkillTree::Clear()
{
	Super::Clear();
	ClearSkillList();
}

void USkillTree::LoadSkillList()
{
	UStatSetPlayer* MyPlayerStat = GameInstance->GetPlayerManager()->GetStatSet();
	if (IsValid(MyPlayerStat) == false)
	{
		DEBUG_MESSAGE;
		return;
	}
	ECharacterMainJobType MyJob = MyPlayerStat->GetMainJob();

	ClearSkillList();

	TArray<FSkillData> SkillList;
	GameInstance->GetDataManager()->GetSkillListByJob(MyJob, SkillList);

	//가져온 스킬 데이터를 UI로 띄워준다.
	for (const FSkillData& SkillData : SkillList)
	{
		ESkillGroup SkillGroup = SkillData.SkillGroup;
		if (SkillGroup == ESkillGroup::NONE)
			continue;

		switch (SkillGroup)
		{
		case ESkillGroup::NORMAL:
			NormalSkillWrapBox->AddChild(SkillData);
			break;
		case ESkillGroup::UNIQUE:
			UniqueSkillWrapBox->AddChild(SkillData);
			break;
		case ESkillGroup::ULTIMATE:
			UltimateSkillWrapBox->AddChild(SkillData);
			break;
		default:
			break;
		}
	}

	NormalSkillWrapBox->RefreshUI();
	UniqueSkillWrapBox->RefreshUI();
	UltimateSkillWrapBox->RefreshUI();

}

void USkillTree::ClearSkillList()
{
	NormalSkillWrapBox->Clear();
	UniqueSkillWrapBox->Clear();
	UltimateSkillWrapBox->Clear();
}

