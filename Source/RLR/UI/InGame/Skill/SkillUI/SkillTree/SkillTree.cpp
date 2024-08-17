// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillTree/SkillTree.h"
#include "UI/InGame/Skill/SkillUI/SkillTree/SkillTreeSlot.h"
#include "UI/InGame/Skill/SkillUI/SkillTree/SkillPropertyContainer.h"
#include "UI/InGame/Skill/SkillUI/SkillTree/SkillPropertySlot.h"

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

}

void USkillTree::RefreshUI()
{
	Super::RefreshUI();


	/*
		자기의 클래스 정보에 맞는 스킬 정보를 불러온다.
	*/
	UStatSetPlayer* MyPlayerStat = GameInstance->GetPlayerManager()->GetStatSet();
	ECharacterMainJobType MyJob;

	if (IsValid(MyPlayerStat) == false)
	{
		/*
			임시 코드. 서버 연결이 안된 클라이언트 테스트 용
			지금은 단순하게 전사로 판단한다.
		*/
		MyJob = ECharacterMainJobType::SWORDSMAN;

	}
	else
	{
		MyJob = MyPlayerStat->GetMainJob();
	}

	TArray<FSkillData> SkillList; 
	GameInstance->GetDataManager()->GetSkillListByJob(MyJob, SkillList);
	
	NormalSkillWrapBox->ClearChildren();
	UniqueSkillWrapBox->ClearChildren();
	UltimateSkillWrapBox->ClearChildren();

	Util::Checkf(SkillTreeSlotClass, TEXT("SkillTreeSlotClass is Null"));

	//가져온 스킬 데이터를 UI로 띄워준다.
	for (FSkillData SkillData : SkillList)
	{
		ESkillGroup SkillGroup = SkillData.SkillGroup;
		if(SkillGroup == ESkillGroup::NONE)
			continue;

		USkillTreeSlot* NewSlot = CreateWidget<USkillTreeSlot>(this, SkillTreeSlotClass);
		NewSlot->SetSkillData(SkillData);
		switch (SkillGroup)
		{
		case ESkillGroup::NORMAL:
			NormalSkillWrapBox->AddChildToWrapBox(NewSlot);
			break;
		case ESkillGroup::UNIQUE:
			UniqueSkillWrapBox->AddChildToWrapBox(NewSlot);
			break;
		case ESkillGroup::ULTIMATE:
			UltimateSkillWrapBox->AddChildToWrapBox(NewSlot);
			break;
		default:
			break;
		}

	}
}

void USkillTree::UpdateNormalSkill()
{
	/*
		일반 스킬 리스트 업데이트
	*/

}

void USkillTree::UpdateUniqueSkill()
{
	/*
		고유 스킬 리스트 업데이트
	*/
}

void USkillTree::UpdateUltimateSkill()
{
	/*
		궁극기 스킬 리스트 업데이트
	*/
}
