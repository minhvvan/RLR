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

void USkillTreeSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void USkillTreeSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

FReply USkillTreeSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	/*
	스킬 디테일 창에 정보를 넘긴다.
	*/

	UInGameMainUI* InGameMainUI = Cast<UInGameMainUI>(GameInstance->GetUIManager()->GetMainUI());
	if (IsValid(InGameMainUI) == false)
		return result;

	USkillUI* SkillUI = InGameMainUI->SkillUI;
	if (IsValid(SkillUI) == false)
		return result;

	SkillUI->UpdateSkillDetailInfo(GetSkillData());
	return result;
}

void USkillTreeSlot::RefreshUI()
{
	Super::RefreshUI();
	SetSlotImage(GetActionResource().ActionImage);
}
