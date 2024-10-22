// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingListSlot.h"
#include "UI/InGame/Skill/SkillUI/SkillUI.h"
#include "UI/InGame/Skill/SkillUI/SkillDetailInfo.h"
#include "UI/InGame/InGameMainUI.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/UIManager.h"


void USkillSettingListSlot::NativeConstruct()
{
	Super::NativeConstruct();
	SetSlotType(ESlotType::SKILL_SETTING_LIST_SLOT);
}

void USkillSettingListSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if(IsLearned == false)
		return;

	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

FReply USkillSettingListSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (GetSkillData() == FSkillData::EmptySkillData)
		return result;

	UInGameMainUI* InGameMainUI = Cast<UInGameMainUI>(GameInstance->GetUIManager()->GetMainUI());
	if (IsValid(InGameMainUI) == false)
		return result;

	USkillUI* SkillUI = InGameMainUI->SkillUI;
	if (IsValid(SkillUI) == false)
		return result;

	SkillUI->UpdateSkillDetailInfo(GetSkillData());

	return result;
}


void USkillSettingListSlot::RefreshUI()
{
	Super::RefreshUI();

	if(GetSkillData() ==FSkillData::EmptySkillData)
		return;
	int32 SkillSeq = GetSkillData().SkillSeq;

	FSkillClass SkillClassData = GameInstance->GetDataManager()->GetSkillResource(SkillSeq);
	if(SkillClassData == FSkillClass::EmptySkillClass)
		return;

	if (IsValid(SkillClassData.SkillImage) == true)
	{
		SetSlotImage(SkillClassData.SkillImage);
	}

	SkillLevelText->SetText(FText::AsNumber(GetSkillData().Level));
	SkillNameText->SetText(GetSkillData().Name);

	if (IsEquipped == true)
	{
		EquipStateText->SetVisibility(ESlateVisibility::Visible);
	}
	else if (IsEquipped == false)
	{
		EquipStateText->SetVisibility(ESlateVisibility::Hidden);
	}

	if (IsLearned == true)
	{
		FLinearColor DefaultColor = FLinearColor::White;
		SlotImage->SetColorAndOpacity(DefaultColor);
	}
	else if (IsLearned == false)
	{
		FLinearColor DarkColor = FLinearColor(1, 1, 1, 0.5f); // 반투명한 검정색
		SlotImage->SetColorAndOpacity(DarkColor);
	}
}

void USkillSettingListSlot::SetEquipped(bool Value)
{
	IsEquipped = Value;
}

void USkillSettingListSlot::SetLearned(bool Value)
{
	IsLearned = Value;
}
