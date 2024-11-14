// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/CharacterStatusDisplay/StatusDisplay.h"
#include "UI/InGame/CharacterStatusDisplay/ProgressGlobe.h"
#include "UI/InGame/CharacterStatusDisplay/ExpProgressBar.h"
#include "UI/InGame/CharacterStatusDisplay/SkillQuickSlot.h"
#include "UI/InGame/CharacterStatusDisplay/SkillQuickSlotContainer.h"
#include "UI/InGame/CharacterStatusDisplay/ItemQuickSlotContainer.h"
#include "UI/InGame/CharacterStatusDisplay/ItemQuickSlot.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "GameManager/RLRStruct.h"
#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/SkillManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/InventoryManager.h"
#include "GameOptionData/GameOptionData.h"

#include "Structs/PlayerStructs.h"
#include "Structs/UtilStructs.h"

void UStatusDisplay::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance->GetSkillManager()->UpdatedTryActivateAction.RemoveDynamic(this, &UStatusDisplay::UpdateSkillQuickSlot);
	GameInstance->GetSkillManager()->UpdatedTryActivateAction.AddUniqueDynamic(this, &UStatusDisplay::UpdateSkillQuickSlot);

	GameInstance->GetInventoryManager()->UpdatedTryUsingItemAction.RemoveDynamic(this, &UStatusDisplay::UpdateItemQuickSlot);
	GameInstance->GetInventoryManager()->UpdatedTryUsingItemAction.AddUniqueDynamic(this, &UStatusDisplay::UpdateItemQuickSlot);

	GameInstance->GetInventoryManager()->UpdatedItemSettingDelegate.RemoveDynamic(this, &UStatusDisplay::SaveItemQuickSlotData);
	GameInstance->GetInventoryManager()->UpdatedItemSettingDelegate.AddUniqueDynamic(this, &UStatusDisplay::SaveItemQuickSlotData);
}

void UStatusDisplay::Init()
{
	Super::Init();
}

void UStatusDisplay::RefreshUI()
{
	LoadSkillQuickSlotData();
	LoadItemQuickSlotData();
}

void UStatusDisplay::SaveItemQuickSlotData()
{
	/*
		현재 세팅 되어 있는 아이템 퀵 슬롯 저장
	*/

	UGameOptionData* GameOption = GameInstance->GetGameOptionData();
	if (CHECK_VALID(GameOption) == false)
		return;

	int32 UserSeq = GetGameManager()->GetUserSeq();
	TMap<FGameplayTag, int32>& QuickSlotList = GameOption->GetItemQuickSlotOption().ItemQuickSlotList;
	const FSkillDictionary<FGameplayTag, FItemData>& OwnItems = GetInventoryManager()->GetOwnItems();

	for (auto& [Tag, Data] : OwnItems)
	{
		if (QuickSlotList.Contains(Tag) == true)
		{
			QuickSlotList[Tag] = Data.ITEM_SEQ;
		}
	}

	GameInstance->SaveGameOption();
	LoadItemQuickSlotData();
}

void UStatusDisplay::LoadSkillQuickSlotData()
{
	SkillQuickSlotContainer->RefreshUI();
}

void UStatusDisplay::LoadItemQuickSlotData()
{
	ItemQuickSlotContainer->RefreshUI();
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

void UStatusDisplay::UpdateSkillQuickSlot(FGameplayTag ActionTag)
{
	/*
		TODO. 스킬 쿨타임 돌려주자.
	*/
	USkillQuickSlot* UpdatedSlot = GetSkillQuickSlot(ActionTag);
	if(IsValid(UpdatedSlot) == false)
		return;
	UpdatedSlot->UpdatedSkillQuickSlot();
}

void UStatusDisplay::UpdateItemQuickSlot(FGameplayTag ActionTag)
{
	/*
		TODO. 
		포션, 기타 소모 아이템... 
		이런 아이템들을 사용하면 퀵 슬롯에 남은 갯수나 쿨타임 업데이트가 되어야 한다.
	*/

	UItemQuickSlot* UpdatedSlot = GetItemQuickSlot(ActionTag);
	if (IsValid(UpdatedSlot) == false)
		return;
	UpdatedSlot->UpdatedItemQuickSlot();
}

USkillQuickSlot* UStatusDisplay::GetSkillQuickSlot(FGameplayTag ActionTag)
{
	if(SkillQuickSlotContainer->QuickSlotMap.Contains(ActionTag) == false)
		return nullptr;
	return  SkillQuickSlotContainer->QuickSlotMap[ActionTag];
}

UItemQuickSlot* UStatusDisplay::GetItemQuickSlot(FGameplayTag ActionTag)
{
	if (ItemQuickSlotContainer->QuickSlotMap.Contains(ActionTag) == false)
		return nullptr;
	return ItemQuickSlotContainer->QuickSlotMap[ActionTag];
}