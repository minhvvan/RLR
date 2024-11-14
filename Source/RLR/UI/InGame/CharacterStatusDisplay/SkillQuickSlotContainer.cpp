// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/CharacterStatusDisplay/SkillQuickSlotContainer.h"
#include "UI/InGame/CharacterStatusDisplay/SkillQuickSlot.h"

#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"
#include "GameOptionData/GameOptionData.h"

#include "Components/GridPanel.h"

void USkillQuickSlotContainer::NativeConstruct()
{
	Super::NativeConstruct();

}

void USkillQuickSlotContainer::Init()
{
	Super::Init();
	
	TSubclassOf<USkillQuickSlot> SlotClass = GetWidgetClass<USkillQuickSlot>("WBP_SkillQuickSlot");
	if (CHECK_VALID(SlotClass) == false)
		return;

	UGameOptionData* GameOption = GameInstance->GetGameOptionData();
	if (CHECK_VALID(GameOption) == false)
		return;

	SkillQuickSlotGridPanel->ClearChildren();
	const TMap<FGameplayTag, int32>& QucikSlotList = GameOption->GetSkillQuickSlotOption().SkillQuickSlotList;

	int32 SlotCount = 0;
	for (TTuple<FGameplayTag, int32> Element : QucikSlotList)
	{
		USkillQuickSlot* QuickSlot = CreateWidget<USkillQuickSlot>(this, SlotClass);
		SkillQuickSlotGridPanel->AddChildToGrid(QuickSlot, SlotCount / MaxColunm, SlotCount % MaxColunm);

		FGameplayTag ActionTag = Element.Key;
		QuickSlot->SetActionTag(ActionTag);
		QuickSlot->Clear();

		QuickSlot->SetSlotIndex(SlotCount++);
		QuickSlotMap.Add(ActionTag, QuickSlot);
	}
}

void USkillQuickSlotContainer::RefreshUI()
{
	Super::RefreshUI();
	Clear();

	UGameOptionData* GameOption = GameInstance->GetGameOptionData();
	const TMap<FGameplayTag, int32>& QucikSlotList = GameOption->GetSkillQuickSlotOption().SkillQuickSlotList;

	for (TTuple<FGameplayTag, int32> Element : QucikSlotList)
	{
		FGameplayTag ActionTag = Element.Key;
		int32		 SkillSeq  = Element.Value;

		if(QuickSlotMap.Contains(ActionTag) == false)
			continue;

		USkillQuickSlot* QuickSlot = QuickSlotMap[ActionTag];

		FSkillData SkillData = GetDataManager()->GetSkillData(SkillSeq);
		if (SkillData == FSkillData::EmptySkillData)
		{
			QuickSlot->RefreshUI();
			continue;
		}
		FActionResource ActionResource = GetDataManager()->GetActionResource(SkillSeq);
		if (ActionResource == FActionResource::EmptyActionResource)
		{
			QuickSlot->RefreshUI();
			continue;
		}
		QuickSlot->SetSkillData(SkillData);		
		QuickSlot->SetActionResource(ActionResource);
	}
}

void USkillQuickSlotContainer::Clear()
{
	Super::Clear();

	for (TTuple<FGameplayTag, USkillQuickSlot*> Element : QuickSlotMap)
	{
		USkillQuickSlot* QuickSlot = Element.Value;
		QuickSlot->Clear();
	}
}
