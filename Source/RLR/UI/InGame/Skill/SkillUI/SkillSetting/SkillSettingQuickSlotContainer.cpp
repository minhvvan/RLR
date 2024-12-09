// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingQuickSlotContainer.h"
#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingQuickSlot.h"

#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameOptionData/GameOptionData.h"

void USkillSettingQuickSlotContainer::Init()
{
	TSubclassOf<USkillSettingQuickSlot> SlotClass = GameInstance->GetDataManager()->GetWidgetClass<USkillSettingQuickSlot>(RLRLITERAL.WBP_SkillSettingQuickSlot);
	if (CHECK_VALID(SlotClass) == false)
		return;

	UGameOptionData* GameOption = GameInstance->GetGameOptionData();
	if (CHECK_VALID(GameOption) == false)
		return;

	ClearChildren();
	GameOption->GetSkillQuickSlotOption().Init();
	const TMap<FGameplayTag, int32>& QucikSlotList = GameOption->GetSkillQuickSlotOption().SkillQuickSlotList;

	int32 SlotCount = 0;
	for (TTuple<FGameplayTag, int32> Element : QucikSlotList)
	{
		USkillSettingQuickSlot* QuickSlot = CreateWidget<USkillSettingQuickSlot>(this, SlotClass);
		AddChildToUniformGrid(QuickSlot, SlotCount / 4, SlotCount % 4);

		FGameplayTag ActionTag = Element.Key;
		int32		 SkillID = Element.Value;

		QuickSlot->SetActionTag(ActionTag);
		QuickSlot->Clear();
		QuickSlot->SetSlotIndex(SlotCount++);
		QuickSlotMap.Add(ActionTag, QuickSlot);
	}
}

void USkillSettingQuickSlotContainer::RefreshUI()
{
	for (TTuple<FGameplayTag, USkillSettingQuickSlot*> Element : QuickSlotMap)
	{
		Element.Value->RefreshUI();
	}
}

void USkillSettingQuickSlotContainer::Clear()
{
	for (TTuple<FGameplayTag, USkillSettingQuickSlot*> Element : QuickSlotMap)
	{
		Element.Value->Clear();
	}
}
