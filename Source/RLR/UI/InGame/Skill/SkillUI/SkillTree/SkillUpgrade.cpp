// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillTree/SkillUpgrade.h"

#include "Components/Button.h"
#include "Structs/UtilStructs.h"
#include "GameManager/GameplayTagManager.h"

void USkillUpgrade::NativeConstruct()
{
	Super::NativeConstruct();

	SetUITag(RLRTAG.UI_SkillUpgrade);

	CloseButton->OnClicked.AddUniqueDynamic(this, &USkillUpgrade::CloseUI);

}

void USkillUpgrade::RefreshUI()
{
	//스킬 데이터가 없으면 닫는다.
	if (!SkillData.IsValid()) return;
	if (*SkillData == FSkillData::EmptySkillData)
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
	SkillData = MakeShared<FSkillData>(NewSkillData);

	RefreshUI();
}
