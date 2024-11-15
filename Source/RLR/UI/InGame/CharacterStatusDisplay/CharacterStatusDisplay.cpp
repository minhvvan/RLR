// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/CharacterStatusDisplay/CharacterStatusDisplay.h"
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

void UCharacterStatusDisplay::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance->GetSkillManager()->UpdatedTryActivateAction.RemoveDynamic(this, &UCharacterStatusDisplay::UpdateSkillQuickSlot);
	GameInstance->GetSkillManager()->UpdatedTryActivateAction.AddUniqueDynamic(this, &UCharacterStatusDisplay::UpdateSkillQuickSlot);

	GameInstance->GetInventoryManager()->UpdatedTryUsingItemAction.RemoveDynamic(this, &UCharacterStatusDisplay::UpdateItemQuickSlot);
	GameInstance->GetInventoryManager()->UpdatedTryUsingItemAction.AddUniqueDynamic(this, &UCharacterStatusDisplay::UpdateItemQuickSlot);

	GameInstance->GetInventoryManager()->UpdatedItemSettingDelegate.RemoveDynamic(this, &UCharacterStatusDisplay::SaveItemQuickSlotData);
	GameInstance->GetInventoryManager()->UpdatedItemSettingDelegate.AddUniqueDynamic(this, &UCharacterStatusDisplay::SaveItemQuickSlotData);
}

void UCharacterStatusDisplay::Init()
{
	Super::Init();
}

void UCharacterStatusDisplay::RefreshUI()
{
	LoadSkillQuickSlotData();
	LoadItemQuickSlotData();
}

void UCharacterStatusDisplay::SaveItemQuickSlotData()
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

void UCharacterStatusDisplay::LoadSkillQuickSlotData()
{
	SkillQuickSlotContainer->RefreshUI();
}

void UCharacterStatusDisplay::LoadItemQuickSlotData()
{
	ItemQuickSlotContainer->RefreshUI();
}

void UCharacterStatusDisplay::UpdateTotalStat(const FTotalStatus& NewTotalStatus)
{
	float hpPercent = FMath::Clamp(NewTotalStatus.HP / NewTotalStatus.MAX_HP, 0.f, 1.f);
	float mpPercent = FMath::Clamp(NewTotalStatus.MP / NewTotalStatus.MAX_MP, 0.f, 1.f);

	UpdateHpGlobe(hpPercent);
	UpdateMpGlobe(mpPercent);
}

void UCharacterStatusDisplay::UpdateHpGlobe(float NewPercent)
{
	HPGlobe->SetGlobePercent(NewPercent);
}

void UCharacterStatusDisplay::UpdateMpGlobe(float NewPercent)
{
	MPGlobe->SetGlobePercent(NewPercent);
}

void UCharacterStatusDisplay::UpdateLevel(int32 NewLevel)
{
	ExpProgressBar->UpdateMaxExp(NewLevel);
}

void UCharacterStatusDisplay::UpdateExp(int32 NewExp)
{
	ExpProgressBar->UpdateExp(NewExp);
}

void UCharacterStatusDisplay::UpdateSkillQuickSlot(FGameplayTag ActionTag)
{
	/*
		TODO. 스킬 쿨타임 돌려주자.
	*/
	USkillQuickSlot* UpdatedSlot = GetSkillQuickSlot(ActionTag);
	if(IsValid(UpdatedSlot) == false)
		return;
	UpdatedSlot->UpdatedSkillQuickSlot();
}

void UCharacterStatusDisplay::UpdateItemQuickSlot(FGameplayTag ActionTag)
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

USkillQuickSlot* UCharacterStatusDisplay::GetSkillQuickSlot(FGameplayTag ActionTag)
{
	if(SkillQuickSlotContainer->QuickSlotMap.Contains(ActionTag) == false)
		return nullptr;
	return  SkillQuickSlotContainer->QuickSlotMap[ActionTag];
}

UItemQuickSlot* UCharacterStatusDisplay::GetItemQuickSlot(FGameplayTag ActionTag)
{
	if (ItemQuickSlotContainer->QuickSlotMap.Contains(ActionTag) == false)
		return nullptr;
	return ItemQuickSlotContainer->QuickSlotMap[ActionTag];
}