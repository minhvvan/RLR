// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSetting.h"
#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingQuickSlot.h"
#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingListSlot.h"
#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingListSlotContainer.h"
#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingQuickSlotContainer.h"

#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/StatusDisplay/StatusDisplay.h"

#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "Player/PlayerCommands.h"

#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/SkillManager.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/NetworkManager.h"
#include "GameOptionData/GameOptionData.h"

#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/UniformGridPanel.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Structs/SkillStructs.h"



void USkillSetting::NativeConstruct()
{
	Super::NativeConstruct();

	NormalSkillTabButton->OnClicked.AddUniqueDynamic(this, &USkillSetting::OnClickedNormalSkillTab);
	UniqueSkillTabButton->OnClicked.AddUniqueDynamic(this, &USkillSetting::OnClickedUniqueSkillTab);
	UltimateSkillTabButton->OnClicked.AddUniqueDynamic(this, &USkillSetting::OnClickedUltimateSkillTab);

	ConfirmButton->OnClicked.AddUniqueDynamic(this, &USkillSetting::OnClickedConfirmButton);
	CancelButton->OnClicked.AddUniqueDynamic(this, &USkillSetting::OnClickedCancelButton);

	USkillManager* SkillManager = GetSkillManager();
	if (IsValid(SkillManager))
	{
		SkillManager->UpdatedSkillSettingDelegate.AddUniqueDynamic(this, &USkillSetting::UpdatedSkillManager);
	}
}

void USkillSetting::Init()
{
	NormalSkillWrapBox->Init();
	UniqueSkillWrapBox->Init();
	UltimateSkillWrapBox->Init();
	SkillQuickSlotGridPanel->Init();
}

void USkillSetting::RefreshUI()
{
	Super::RefreshUI();
	LoadSkillList();
	LoadQuickSlotData();
}

void USkillSetting::Clear()
{
	ClearSkillList();
	ClearQuickSlot();
}

void USkillSetting::ClearSkillList()
{
	NormalSkillWrapBox->Clear();
	UniqueSkillWrapBox->Clear();
	UltimateSkillWrapBox->Clear();
}

void USkillSetting::ClearQuickSlot()
{
	SkillQuickSlotGridPanel->Clear();
}


void USkillSetting::LoadQuickSlotData()
{
	URLRInputConfig* InputConfig = GameInstance->GetDataManager()->GetInputConfig();
	if(CHECK_VALID(InputConfig) == false)
		return;

	UGameOptionData* GameOption = GameInstance->GetGameOptionData();
	if(CHECK_VALID(GameOption) == false)
		return;
	
	ClearQuickSlot();

	//현재 퀵 슬롯 갯수는 8개
	const int32 QuickSlotMaxCount = GameOption->GetSkillQuickSlotOption().SkillQuickSlotList.Num();

	for(int32 CurrentSlotIndex = 0; CurrentSlotIndex < QuickSlotMaxCount; CurrentSlotIndex++ )
	{

		FText FirstKey = FText::Format(FText::FromString("Action.Skill.{0}"), CurrentSlotIndex+1);
		//현재는 그냥 Q,W,E,R 키만 되어 있는데, 나중에 필요하면 Shift + Q 이런거 필요할 때를 위해 SecondKey 흔적만 남겨둔다..
		//FText SecondKey = FText::Format(FText::FromString("Input.{0}"), InputTagKeySelector_2->GetKeySelectionText());

		FGameplayTag FindActionTag = UGameplayTagsManager::Get().RequestGameplayTag(FName(*FirstKey.ToString()), false);

		//Action Tag 값이 제대로 들어가 있는지 확인
		if (FindActionTag != FGameplayTag::EmptyTag)
		{
			USkillSettingQuickSlot* NewQuickSlot = SkillQuickSlotGridPanel->QuickSlotMap[FindActionTag];
			if (IsValid(NewQuickSlot) == false)
			{
				DEBUG_MESSAGE;
				continue;
			}

			//Action Tag에 맞는 input Tag를 찾아야 한다.
			FGameplayTag InputTag = InputConfig->FindInputTagByActionTag(FindActionTag);
			if(InputTag == FGameplayTag::EmptyTag)
				continue;

			NewQuickSlot->SetActionTag(FindActionTag);
			NewQuickSlot->SetInputTag(InputTag);


			/*
				Action Tag <-> Input Tag
				Action Tag <-> Skill Data (SkillId)
			*/

			int32 SkillSeq = -1;
			if (GameOption->GetSkillQuickSlotOption().SkillQuickSlotList.Contains(FindActionTag) == true)
			{
				SkillSeq = GameOption->SkillQuickSlotOption.SkillQuickSlotList[FindActionTag];
			}

			FSkillData QuickSlotSkill = GameInstance->GetDataManager()->GetSkillData(SkillSeq);
			FActionResource QuickSlotSkillClass = GameInstance->GetDataManager()->GetActionResource(SkillSeq);
			NewQuickSlot->SetSkillData(QuickSlotSkill);
			NewQuickSlot->SetActionResource(QuickSlotSkillClass);
			NewQuickSlot->RefreshUI();
		}
	}

}

void USkillSetting::LoadSkillList()
{
	UStatSetPlayer* MyPlayerStat = GameInstance->GetPlayerManager()->GetStatSet();
	if (IsValid(MyPlayerStat) == false)
	{
		DEBUG_MESSAGE;
		return;
	}
	ECharacterMainJobType MyJob = MyPlayerStat->GetMainJob();

	ClearSkillList();

	TArray<FSkillData> SkillList;
	GameInstance->GetDataManager()->GetSkillListByJob(MyJob, SkillList);

	//가져온 스킬 데이터를 UI로 띄워준다.
	for (const FSkillData& SkillData : SkillList)
	{
		ESkillGroup SkillGroup = SkillData.SkillGroup;
		if (SkillGroup == ESkillGroup::NONE)
			continue;

		switch (SkillGroup)
		{
		case ESkillGroup::NORMAL:
			NormalSkillWrapBox->AddChild(SkillData);
			break;
		case ESkillGroup::UNIQUE:
			UniqueSkillWrapBox->AddChild(SkillData);
			break;
		case ESkillGroup::ULTIMATE:
			UltimateSkillWrapBox->AddChild(SkillData);
			break;
		default:
			break;
		}
	}

	NormalSkillWrapBox->RefreshUI();
	UniqueSkillWrapBox->RefreshUI();
	UltimateSkillWrapBox->RefreshUI();
}

void USkillSetting::ReqeustSkillQuickSlotChange()
{
	int32 UserSeq = GetGameManager()->GetPlayerManager()->GetUserSeq();

	const TMap<FGameplayTag, USkillSettingQuickSlot*>& SkillQuickSlotMap = SkillQuickSlotGridPanel->QuickSlotMap;
	for (TTuple<FGameplayTag, TObjectPtr<USkillSettingQuickSlot>> Element : SkillQuickSlotMap)
	{
		const FSkillData& TempData = Element.Value->GetSkillData();
		GetNetworkManager()->SendChangeSkillPacket(&TempData,  Element.Value->GetSlotIndex());
	}
}

void USkillSetting::SaveSkillQuickSlotData()
{
	/*
		현재 세팅 되어 있는 퀵 슬롯 저장
	*/

	UGameOptionData* GameOption = GameInstance->GetGameOptionData();
	if(CHECK_VALID(GameOption) == false)
		return;

	int32 UserSeq = GetGameManager()->GetPlayerManager()->GetUserSeq();
	TMap<FGameplayTag, int32>& QuickSlotList = GameOption->GetSkillQuickSlotOption().SkillQuickSlotList;
	const FSkillDictionary<FGameplayTag, FSkillData>& OwnSkills = GetSkillManager()->GetOwnSkills();

	for (auto& [Tag, Data] : OwnSkills)
	{
		if (QuickSlotList.Contains(Tag) == true)
		{
			QuickSlotList[Tag] = Data.SkillSeq;
		}
	}
	GameInstance->SaveGameOption();
	ApplySkillQuickSlotSetting();
}

void USkillSetting::ApplySkillQuickSlotSetting()
{
	/*
		스킬 퀵 슬롯에 세팅해놓은 걸 Status Display의 스킬 세팅으로 옮겨준다.
	*/

	UInGameMainUI* MainUI = GetUIManager()->GetPage<UInGameMainUI>(FGameplayTagManager::Get().Page_InGame);
	if(IsValid(MainUI) == false)
		return;

	UStatusDisplay* SD = MainUI->GetStatusDisplayUI();
	if(IsValid(SD) == false)
		return;

	SD->LoadSkillQuickSlotData();
}

void USkillSetting::UpdatedSkillManager()
{
	/*
		스킬 퀵 슬롯 세팅이 바뀌거나,
		스킬 정보가 바뀐다거나, 할 때 Skill Manager에서 이벤트를 준다.
	*/
	SaveSkillQuickSlotData();
	RefreshUI();
}

void USkillSetting::ChangeTab(SkillSetting_TabType TabType)
{
	SkillTabSwitcher->SetActiveWidgetIndex((int32)TabType);
	LoadSkillList();
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

void USkillSetting::OnClickedConfirmButton()
{
	//SaveQuickSlotData();
	ReqeustSkillQuickSlotChange();
}

void USkillSetting::OnClickedCancelButton()
{
	LoadQuickSlotData();
}