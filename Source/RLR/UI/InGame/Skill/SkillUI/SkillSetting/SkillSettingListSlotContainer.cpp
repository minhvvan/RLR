// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingListSlotContainer.h"
#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingListSlot.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/SkillManager.h"
#include "GameOptionData/GameOptionData.h"

void USkillSettingListSlotContainer::Init(int32 MaxSlotCount)
{

	TSubclassOf<USkillSettingListSlot> SlotClass = GameInstance->GetDataManager()->GetWidgetClass<USkillSettingListSlot>("WBP_SkillSettingListSlot");
	if (IsValid(SlotClass) == false)
		DEBUG_MESSAGE;

	for(int32 i = 0 ; i < MaxSlotCount; i++)
	{ 
		USkillSettingListSlot* NewSlot = CreateWidget<USkillSettingListSlot>(this, SlotClass);
		NewSlot->Clear();
		SlotMap.Add(i, NewSlot);
		AddChildToWrapBox(NewSlot);
		NewSlot->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USkillSettingListSlotContainer::RefreshUI()
{

	UGameOptionData* GameOption = GameInstance->GetGameOptionData();
	if (IsValid(GameOption) == false)
	{
		DEBUG_MESSAGE;
		return;
	}
	USkillManager* SkillManager = GameInstance->GetSkillManager();

	for (TTuple<int32, USkillSettingListSlot*> Element : SlotMap)
	{
		int32 SlotIndex = Element.Key;
		USkillSettingListSlot* QuickSlot = Element.Value;
		QuickSlot->SetVisibility(ESlateVisibility::Visible);

		FSkillData SkillData = QuickSlot->GetSkillData();
		if (SkillData == FSkillData::EmptySkillData)
		{
			QuickSlot->Clear();
			QuickSlot->SetVisibility(ESlateVisibility::Hidden);
			continue;
		}

		/*
			옵션 정보에서 퀵 슬롯 데이터를 가져와 스킬이 장착 중인지 확인한다.
			장착이 되어 있으면 -장착됨- UI가 뜬다.
			float? 
			int
			double
		*/

		bool IsEquipped = GameOption->GetSkillQuickSlotOption().IsEquippedSkill(SkillData.SkillId);
		QuickSlot->SetEquipped(IsEquipped);

		/*
			아직 배우지 않은 스킬이면, 배우지 않은 스킬이라고 표시해준다.
		*/
		bool HasLearned = SkillManager->HasLearnedSkill(SkillData.SkillSeq);
		QuickSlot->SetLearned(HasLearned);
		QuickSlot->RefreshUI();
	}
}

void USkillSettingListSlotContainer::Clear()
{
	for (TTuple<int32, USkillSettingListSlot*> Element : SlotMap)
	{
		int32 SlotIndex = Element.Key;
		USkillSettingListSlot* QuickSlot = Element.Value;
		QuickSlot->Clear();
		QuickSlot->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USkillSettingListSlotContainer::AddChild(FSkillData SkillData)
{
	for (TTuple<int32, USkillSettingListSlot*> Element : SlotMap)
	{
		const FSkillData& SlotData = Element.Value->GetSkillData();

		//비어 있는 슬롯이면, 해당 빈 슬롯에 데이터를 추가해준다.
		if (SlotData == FSkillData::EmptySkillData)
		{
			Element.Value->SetSkillData(SkillData);
			const FSkillClass& SlotResource = Element.Value->GetSkillClassData();
			Element.Value->SetSkillClassData(SlotResource);
			return;
		}
	}

	//여기까지 오면 Skill List의 슬롯 최대 갯수를 늘려줘야 함.
	DEBUG_MESSAGE;
}
