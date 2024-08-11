// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/StatusDisplay/StatusDisplay.h"
#include "UI/InGame/StatusDisplay/ProgressGlobe.h"
#include "UI/InGame/StatusDisplay/ExpProgressBar.h"
#include "UI/InGame/StatusDisplay/SkillQuickSlot.h"
#include "UI/InGame/StatusDisplay/SkillQuickSlotContainer.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "GameManager/RLRStruct.h"
#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/SkillManager.h"
#include "GameManager/UIManager.h"
#include "GameOptionData/GameOptionData.h"

void UStatusDisplay::NativeConstruct()
{
	Super::NativeConstruct();
	SetUIType(EUIType::STATUSDISPLAY);
	ClearSkillQuickSlot();

	GameInstance->GetSkillManager()->UpdatedTryActivateAction.RemoveDynamic(this, &UStatusDisplay::UpdateSkillAttack);
	GameInstance->GetSkillManager()->UpdatedTryActivateAction.AddUniqueDynamic(this, &UStatusDisplay::UpdateSkillAttack);
}

void UStatusDisplay::RefreshUI()
{
	LoadSkillQuickSlotData();
}

USkillQuickSlot* UStatusDisplay::GetSkillQuickSlot(FGameplayTag ActionTag)
{
	return SkillQuickSlotMap[ActionTag];
}

void UStatusDisplay::LoadSkillQuickSlotData()
{
	//GameOption에 저장되어 있는 Skill Quick Slot Data를 불러온다.
	if (IsValid(SkillQuickSlotClass) == false)
	{
		DEBUG_LOG("LoadSkillQuickSlotData Error. SkillQuickSlotClass is Null.");
		return;
	}

	UGameOptionData* GameOption = GameInstance->GetGameOptionData();
	if(IsValid(GameOption) == false)
		return;

	FSkillQuickSlotOption QuickOption = GameOption->GetSkillQuickSlotOption();

	//그리드 채우기용
	int32 cnt = 0;

	for (TTuple<FGameplayTag, int32> Element : QuickOption.SkillQuickSlotList)
	{
		FGameplayTag ActionTag = Element.Key;
		int32 SkillID = Element.Value;

		if (SkillQuickSlotMap.Contains(ActionTag) == false)
		{
			USkillQuickSlot* NewSkillQuickSlot = CreateWidget<USkillQuickSlot>(this,SkillQuickSlotClass);
			SkillQuickSlotMap.Add(ActionTag, NewSkillQuickSlot);
			SkillQuickSlotContainer->AddChild(NewSkillQuickSlot, cnt++);
		}

		USkillQuickSlot* FindSkillQuickSlot = SkillQuickSlotMap[ActionTag];

		if (IsValid(FindSkillQuickSlot) == false)
		{
			Util::Checkf(FindSkillQuickSlot, "LoadSkillQuickSlotData Error");
			continue;
		}

		FSkillData SlotSkill = GameInstance->GetDataManager()->GetSkillData(SkillID);
		FindSkillQuickSlot->SetSkillData(SlotSkill);
		FindSkillQuickSlot->SetActionTag(ActionTag);
		FindSkillQuickSlot->RefreshUI();
	}
}

void UStatusDisplay::ClearSkillQuickSlot()
{
	SkillQuickSlotContainer->Clear();
	SkillQuickSlotMap.Empty();
}

void UStatusDisplay::UpdateTotalStat(const FTotalStatus& NewTotalStatus)
{
	float hpPercent = FMath::Clamp(NewTotalStatus.HP / NewTotalStatus.MAX_HP, 0.f, 1.f);
	float mpPercent = FMath::Clamp(NewTotalStatus.HP / NewTotalStatus.MAX_HP, 0.f, 1.f);

	UpdateHpGlobe(hpPercent);
	UpdateMpGlobe(mpPercent);
}

void UStatusDisplay::UpdateHpGlobe(float NewPercent)
{
	HPGlobe->SetGlobePercent(NewPercent);
}

void UStatusDisplay::UpdateMpGlobe(float NewPercent)
{
	MPGlobe->SetGlobePercent(NewPercent);
}

void UStatusDisplay::UpdateLevel(int32 NewLevel)
{
	ExpProgressBar->UpdateMaxExp(NewLevel);
}

void UStatusDisplay::UpdateExp(int32 NewExp)
{
	ExpProgressBar->UpdateExp(NewExp);
}

void UStatusDisplay::UpdateSkillAttack(FGameplayTag ActionTag)
{
	USkillQuickSlot* UpdatedSlot = GetSkillQuickSlot(ActionTag);
	if(IsValid(UpdatedSlot) == false)
		return;
	UpdatedSlot->UpdatedSkillAttack();
}
