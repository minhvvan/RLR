// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSetting.h"
#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingQuickSlot.h"
#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingListSlot.h"

#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "Player/PlayerCommands.h"

#include "GameManager/RLRStruct.h"
#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/GameplayTagManager.h"
#include "GameOptionData/GameOptionData.h"

#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"



void USkillSetting::NativeConstruct()
{
	Super::NativeConstruct();

	NormalSkillTabButton->OnClicked.AddUniqueDynamic(this, &USkillSetting::OnClickedNormalSkillTab);
	UniqueSkillTabButton->OnClicked.AddUniqueDynamic(this, &USkillSetting::OnClickedUniqueSkillTab);
	UltimateSkillTabButton->OnClicked.AddUniqueDynamic(this, &USkillSetting::OnClickedUltimateSkillTab);



}

void USkillSetting::RefreshUI()
{
	Super::RefreshUI();

	LoadSkillList();
	LoadQuickSlotData();
}


void USkillSetting::OnClickedNormalSkillTab()
{
	ChangeTab(SkillSetting_TabType::NORMAL);
}

void USkillSetting::OnClickedUniqueSkillTab()
{
	ChangeTab(SkillSetting_TabType::UNIQUE);
}

void USkillSetting::OnClickedUltimateSkillTab()
{
	ChangeTab(SkillSetting_TabType::ULTIMATE);
}

void USkillSetting::LoadQuickSlotData()
{

	//스킬 슬롯 갯수는 현재 8개. 하지만 미래에 혹시 모르니 일단 무식하게 범위를 잡는다.


	URLRInputConfig* InputConfig = GameInstance->GetDataManager()->GetInputConfig();
	if(IsValid(InputConfig) == false)
	{
		DEBUG_LOG("Load Quick Slot Data Error. InputConfig is Null");
		return;
	}

	UGameOptionData* GameOption = GameInstance->GetGameOptionData();
	if (IsValid(GameOption) == false)
	{
		DEBUG_LOG("Load Quick Slot Data Error. GameOption is Null");
		return;
	}

	for(int i = 1; i <= 20; i++ )
	{
		FText FirstKey = FText::Format(FText::FromString("Action.Skill.{0}.Anim"), i);
		//FText SecondKey = FText::Format(FText::FromString("Input.{0}"), InputTagKeySelector_2->GetKeySelectionText());

		FGameplayTag FindTag = UGameplayTagsManager::Get().RequestGameplayTag(FName(*FirstKey.ToString()), false);

		if (FindTag != FGameplayTag::EmptyTag)
		{

			USkillSettingQuickSlot* NewQuickSlot = nullptr;
			if (SkillQuickSlotMap.Contains(FindTag) == false)
			{ 

				NewQuickSlot = CreateWidget<USkillSettingQuickSlot>(this, SkillSettingQuickSlotClass);
				if (IsValid(NewQuickSlot) == false)
					continue;

				SkillQuickSlotMap.Add(FindTag, NewQuickSlot);


			}
			else if (SkillQuickSlotMap.Contains(FindTag) == true)
			{

				NewQuickSlot = SkillQuickSlotMap[FindTag];

			}

			//Action Tag에 맞는 input Tag를 찾아야 한다.
			FGameplayTag InputTag = InputConfig->FindInputTagByActionTag(FindTag);
			if(InputTag == FGameplayTag::EmptyTag)
				continue;

			NewQuickSlot->SetActionTag(FindTag);
			NewQuickSlot->SetInputTag(InputTag);


			/*
				Action Tag <-> Input Tag
				Action Tag <-> Skill Data (SkillId)
			*/

			int32 SkillId = -1;
			if (GameOption->GetSkillQuickSlotOption().SkillQuickSlotList.Contains(FindTag) == true)
			{
				SkillId = GameOption->SkillQuickSlotOption.SkillQuickSlotList[FindTag];
			}


			FSkillData QuickSlotSkill = GameInstance->GetDataManager()->GetSkillData(SkillId);
			NewQuickSlot->SetSkillData(QuickSlotSkill);
			NewQuickSlot->RefreshUI();
		}
	}

}

void USkillSetting::LoadSkillList()
{
	UStatSetPlayer* MyPlayerStat = GameInstance->GetPlayerManager()->GetStatSet();
	ECharacterMainJobType MyJob;

	UGameOptionData* GameOption = GameInstance->GetGameOptionData();
	if (IsValid(GameOption) == false)
	{
		DEBUG_LOG("Load Quick Slot Data Error. GameOption is Null");
		return;
	}

	if (IsValid(MyPlayerStat) == false)
	{
		/*
			임시 코드. 서버 연결이 안된 클라이언트 테스트 용
			지금은 단순하게 전사로 판단한다.
		*/
		MyJob = ECharacterMainJobType::SWORDSMAN;

	}
	else
	{
		MyJob = MyPlayerStat->GetMainJob();
	}

	TArray<FSkillData> SkillList;
	GameInstance->GetDataManager()->GetSkillListByJob(MyJob, SkillList);

	NormalSkillWrapBox->ClearChildren();
	UniqueSkillWrapBox->ClearChildren();
	UltimateSkillWrapBox->ClearChildren();

	Util::Checkf(SkillSettingListSlotClass, TEXT("SkillSettingListSlotClass is Null"));

	//가져온 스킬 데이터를 UI로 띄워준다.
	for (FSkillData SkillData : SkillList)
	{
		ESkillGroup SkillGroup = SkillData.SkillGroup;
		if (SkillGroup == ESkillGroup::NONE)
			continue;

		USkillSettingListSlot* NewSlot = CreateWidget<USkillSettingListSlot>(this, SkillSettingListSlotClass);
		NewSlot->SetSkillData(SkillData);


		/*
			옵션 정보에서 퀵 슬롯 데이터를 가져와 장착 중인 스킬 정보를 찾는다.
		*/

		bool IsEquipped = GameOption->GetSkillQuickSlotOption().IsEquippedSkill(SkillData.SkillId);
		NewSlot->SetEquipped(IsEquipped);


		switch (SkillGroup)
		{
		case ESkillGroup::NORMAL:
			NormalSkillWrapBox->AddChildToWrapBox(NewSlot);
			break;
		case ESkillGroup::UNIQUE:
			UniqueSkillWrapBox->AddChildToWrapBox(NewSlot);
			break;
		case ESkillGroup::ULTIMATE:
			UltimateSkillWrapBox->AddChildToWrapBox(NewSlot);
			break;
		default:
			break;
		}
	}
}

void USkillSetting::SaveQuickSlotData()
{
	/*
		TODO
	*/

	UGameOptionData* GameOption = GameInstance->GetGameOptionData();
	if (IsValid(GameOption) == false)
	{
		DEBUG_LOG("LSaveQuickSlotData. GameOption is Null");
		return;
	}

	for (TTuple<FGameplayTag, TObjectPtr<USkillSettingQuickSlot>> Element : SkillQuickSlotMap)
	{
		if(Element.Value->IsEmpty() == true)
			continue;

		TMap<FGameplayTag, int32>& QuickSlotList = GameOption->GetSkillQuickSlotOption().SkillQuickSlotList;

		if (QuickSlotList.Contains(Element.Key) == true)
		{
			
			QuickSlotList[Element.Key] = Element.Value->SkillData.SkillId;

		}

	}
	

}

void USkillSetting::ChangeTab(SkillSetting_TabType TabType)
{
	SkillTabSwitcher->SetActiveWidgetIndex((int32)TabType);
	LoadSkillList();
}
