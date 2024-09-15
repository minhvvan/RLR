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
#include "Structs/PlayerStructs.h"
#include "Structs/UtilStructs.h"

void UStatusDisplay::NativeConstruct()
{
	Super::NativeConstruct();
	SetUIType(EUIType::STATUSDISPLAY);

	GameInstance->GetSkillManager()->UpdatedTryActivateAction.RemoveDynamic(this, &UStatusDisplay::UpdateSkillAttack);
	GameInstance->GetSkillManager()->UpdatedTryActivateAction.AddUniqueDynamic(this, &UStatusDisplay::UpdateSkillAttack);
}

void UStatusDisplay::Init()
{
	Super::Init();
}

void UStatusDisplay::RefreshUI()
{
	LoadSkillQuickSlotData();
}

USkillQuickSlot* UStatusDisplay::GetSkillQuickSlot(FGameplayTag ActionTag)
{
	return  nullptr; //SkillQuickSlotMap[ActionTag];
}

void UStatusDisplay::LoadSkillQuickSlotData()
{
	SkillQuickSlotContainer->RefreshUI();
}

void UStatusDisplay::UpdateTotalStat(const FTotalStatus& NewTotalStatus)
{
	float hpPercent = FMath::Clamp(NewTotalStatus.HP / NewTotalStatus.MAX_HP, 0.f, 1.f);
	float mpPercent = FMath::Clamp(NewTotalStatus.MP / NewTotalStatus.MAX_MP, 0.f, 1.f);

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
