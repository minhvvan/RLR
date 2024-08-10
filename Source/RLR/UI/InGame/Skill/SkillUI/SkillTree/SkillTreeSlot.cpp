// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillTree/SkillTreeSlot.h"
#include "UI/InGame/Skill/SkillUI/SkillUI.h"
#include "UI/InGame/Skill/SkillUI/SkillDetailInfo.h"
#include "UI/InGame/InGameMainUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"



void USkillTreeSlot::NativeConstruct()
{
	Super::NativeConstruct();

}

void USkillTreeSlot::OnClickedSlotButton()
{
	Super::OnClickedSlotButton();

	/*
		스킬 디테일 창에 정보를 넘긴다.
	*/
	
	UInGameMainUI* InGameMainUI = Cast<UInGameMainUI>(GameInstance->GetUIManager()->GetMainUI());
	if(IsValid(InGameMainUI) == false)
		return;

	USkillUI* SkillUI = InGameMainUI->SkillUI;
	if(IsValid(SkillUI) == false)
		return;

	SkillUI->UpdateSkillDetailInfo(SkillData);
}

void USkillTreeSlot::OnHoveredSlotButton()
{
	Super::OnHoveredSlotButton();

}

void USkillTreeSlot::OnUnHoveredSlotButton()
{
	Super::OnUnHoveredSlotButton();

}

void USkillTreeSlot::SetSkillData(FSkillData& NewSkillData)
{
	SkillData = NewSkillData;
	RefreshUI();
}

void USkillTreeSlot::RefreshUI()
{
	Super::RefreshUI();



}
