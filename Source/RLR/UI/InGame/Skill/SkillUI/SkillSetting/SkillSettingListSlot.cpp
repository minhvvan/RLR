// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingListSlot.h"
#include "UI/InGame/Skill/SkillUI/SkillUI.h"
#include "UI/InGame/Skill/SkillUI/SkillDetailInfo.h"
#include "UI/InGame/InGameMainUI.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"


void USkillSettingListSlot::NativeConstruct()
{
	Super::NativeConstruct();

}

void USkillSettingListSlot::RefreshUI()
{
	Super::RefreshUI();

	if(SkillData ==FSkillData::EmptySkillData)
		return;


	if (IsValid(SkillData.SkillImage) == true)
	{
		SetSlotImage(SkillData.SkillImage);
	}

	SkillLevelText->SetText(FText::AsNumber(SkillData.Level));
	SkillNameText->SetText(FText::FromString(SkillData.Name));

	if (IsEquipped == true)
	{
		EquipStateText->SetVisibility(ESlateVisibility::Visible);
	}
	else if (IsEquipped == false)
	{
		EquipStateText->SetVisibility(ESlateVisibility::Hidden);
	}

}

void USkillSettingListSlot::SetEquipped(bool Value)
{
	IsEquipped = Value;
	RefreshUI();
}

void USkillSettingListSlot::OnClickedSlotButton()
{
	Super::OnClickedSlotButton();

	if(SkillData == FSkillData::EmptySkillData)
		return;

	UInGameMainUI* InGameMainUI = Cast<UInGameMainUI>(GameInstance->GetUIManager()->GetMainUI());
	if (IsValid(InGameMainUI) == false)
		return;

	USkillUI* SkillUI = InGameMainUI->SkillUI;
	if (IsValid(SkillUI) == false)
		return;

	SkillUI->UpdateSkillDetailInfo(SkillData);
}

void USkillSettingListSlot::SetSkillData(FSkillData& NewSkilData)
{
	if (NewSkilData == FSkillData::EmptySkillData)
	{
		RemoveFromParent();
		return;
	}

	SkillData = NewSkilData;
	RefreshUI();
}
