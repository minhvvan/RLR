// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillTree/SkillTreeSlot.h"
#include "UI/InGame/Skill/SkillUI/SkillUI.h"
#include "UI/InGame/Skill/SkillUI/SkillDetailInfo.h"
#include "UI/InGame/InGameMainUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"

#include "Components/Image.h"



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

	auto UIManager = GetUIManager();
	if (!UIManager) return result;

	USkillUI* SkillUI = UIManager->GetSubUI<USkillUI>(RLRTAG.UI_Skill);
	if (IsValid(SkillUI) == false) 
		return result;

	SkillUI->UpdateSkillDetailInfo(GetSkillData());
	return result;
}

void USkillTreeSlot::RefreshUI()
{
	Super::RefreshUI();

	if (GetSkillData() == FSkillData::EmptySkillData)
	{
		SetSlotImage(GetDefaultSlotImage());
		SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	SetVisibility(ESlateVisibility::Visible);

	if (IsValid(GetActionResource().ActionImage) == true)
	{
		SetSlotImage(GetActionResource().ActionImage);
	}

	if (IsLearned == true)
	{
		FLinearColor DefaultColor = FLinearColor::White;
		SlotImage->SetColorAndOpacity(DefaultColor);
	}
	else
	{
		FLinearColor DarkColor = FLinearColor(1, 1, 1, 0.5f); // 반투명한 검정색
		SlotImage->SetColorAndOpacity(DarkColor);
	}
}

void USkillTreeSlot::SetLearned(bool Value)
{
	IsLearned = Value;
	SetSlotImage(GetActionResource().ActionImage);
}
