// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSetting.h"
#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingQuickSlot.h"
#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingListSlot.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/StatusDisplay/StatusDisplay.h"

#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "Player/PlayerCommands.h"

#include "GameManager/RLRStruct.h"
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



void USkillSetting::NativeConstruct()
{
	Super::NativeConstruct();

	NormalSkillTabButton->OnClicked.AddUniqueDynamic(this, &USkillSetting::OnClickedNormalSkillTab);
	UniqueSkillTabButton->OnClicked.AddUniqueDynamic(this, &USkillSetting::OnClickedUniqueSkillTab);
	UltimateSkillTabButton->OnClicked.AddUniqueDynamic(this, &USkillSetting::OnClickedUltimateSkillTab);

	ConfirmButton->OnClicked.AddUniqueDynamic(this, &USkillSetting::OnClickedConfirmButton);
	CancelButton->OnClicked.AddUniqueDynamic(this, &USkillSetting::OnClickedCancelButton);

	Clear();

	USkillManager* SkillManager = GetSkillManager();
	if (IsValid(SkillManager))
	{
		SkillManager->UpdatedSkillManager.AddUniqueDynamic(this, &USkillSetting::UpdatedSkillManager);
	}
}

void USkillSetting::RefreshUI()
{
	Super::RefreshUI();

	Clear();
	LoadSkillList();
	LoadQuickSlotData();
}

void USkillSetting::Clear()
{
	NormalSkillWrapBox->ClearChildren();
	UniqueSkillWrapBox->ClearChildren();
	UltimateSkillWrapBox->ClearChildren();


	SkillQuickSlotMap.Empty();
	SkillQuickSlotGridPanel->ClearChildren();
}

void USkillSetting::ClearSkillList()
{
	NormalSkillWrapBox->ClearChildren();
	UniqueSkillWrapBox->ClearChildren();
	UltimateSkillWrapBox->ClearChildren();

}

void USkillSetting::ClearQuickSlot()
{
	SkillQuickSlotMap.Empty();
	SkillQuickSlotGridPanel->ClearChildren();
}


void USkillSetting::LoadQuickSlotData()
{
	
	ClearQuickSlot();

	URLRInputConfig* InputConfig = GameInstance->GetDataManager()->GetInputConfig();
	if(CHECK_VALID(InputConfig) == false)
		return;

	UGameOptionData* GameOption = GameInstance->GetGameOptionData();
	if(CHECK_VALID(GameOption) == false)
		return;

	TSubclassOf<USkillSettingQuickSlot> SlotClass = GetWidgetClass<USkillSettingQuickSlot>("WBP_SkillSettingQuickSlot");
	if(CHECK_VALID(SlotClass) == false)
		return;
	
	const int32 QuickSlotCount = GameOption->GetSkillQuickSlotOption().SkillQuickSlotList.Num();

	for(int32 CurrentSlotIndex = 0; CurrentSlotIndex < QuickSlotCount; CurrentSlotIndex++ )
	{
		FText FirstKey = FText::Format(FText::FromString("Action.Skill.{0}.Anim"), CurrentSlotIndex+1);
		//FText SecondKey = FText::Format(FText::FromString("Input.{0}"), InputTagKeySelector_2->GetKeySelectionText());

		FGameplayTag FindActionTag = UGameplayTagsManager::Get().RequestGameplayTag(FName(*FirstKey.ToString()), false);

		if (FindActionTag != FGameplayTag::EmptyTag)
		{

			USkillSettingQuickSlot* NewQuickSlot = nullptr;
			if (SkillQuickSlotMap.Contains(FindActionTag) == false)
			{ 

				NewQuickSlot = CreateWidget<USkillSettingQuickSlot>(this, SlotClass);
				if (IsValid(NewQuickSlot) == false)
					continue;

				SkillQuickSlotMap.Add(FindActionTag, NewQuickSlot);
				SkillQuickSlotGridPanel->AddChildToUniformGrid(NewQuickSlot, CurrentSlotIndex / MaxColunm, CurrentSlotIndex % MaxColunm);
				NewQuickSlot->SetSlotIndex(CurrentSlotIndex);
			}
			else if (SkillQuickSlotMap.Contains(FindActionTag) == true)
			{

				NewQuickSlot = SkillQuickSlotMap[FindActionTag];

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

			int32 SkillId = -1;
			if (GameOption->GetSkillQuickSlotOption().SkillQuickSlotList.Contains(FindActionTag) == true)
			{
				SkillId = GameOption->SkillQuickSlotOption.SkillQuickSlotList[FindActionTag];
			}


			FSkillData QuickSlotSkill = GameInstance->GetDataManager()->GetSkillData(SkillId);
			NewQuickSlot->SetSkillData(QuickSlotSkill);
			NewQuickSlot->RefreshUI();
		}
	}

}

void USkillSetting::LoadSkillList()
{
	ClearSkillList();

	UStatSetPlayer* MyPlayerStat = GameInstance->GetPlayerManager()->GetStatSet();
	ECharacterMainJobType MyJob = ECharacterMainJobType::NONE;

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
			나중에 프로젝트가 합쳐지면 마져 이어준다.
			
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

	TSubclassOf<USkillSettingListSlot> SlotClass = GetWidgetClass<USkillSettingListSlot>("WBP_SkillSettingListSlot");

	//가져온 스킬 데이터를 UI로 띄워준다.
	for (FSkillData SkillData : SkillList)
	{
		ESkillGroup SkillGroup = SkillData.SkillGroup;
		if (SkillGroup == ESkillGroup::NONE)
			continue;

		USkillSettingListSlot* NewSlot = CreateWidget<USkillSettingListSlot>(this, SlotClass);
		NewSlot->SetSkillData(SkillData);


		/*
			옵션 정보에서 퀵 슬롯 데이터를 가져와 스킬이 장착 중인지 확인한다.
			장착이 되어 있으면 -장착됨- UI가 뜬다.
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

void USkillSetting::ReqeustSkillQuickSlotChange()
{
	int32 UserSeq = GetGameManager()->GetPlayerManager()->GetUserSeq();
	for (TTuple<FGameplayTag, TObjectPtr<USkillSettingQuickSlot>> Element : SkillQuickSlotMap)
	{

		const FSkillData& TempData = Element.Value->GetSkillData();
		GetNetworkManager()->SendChangeSkillPacket(&TempData, UserSeq, Element.Value->GetSlotIndex());
	}
}

void USkillSetting::SaveQuickSlotData()
{
	/*
		현재 세팅 되어 있는 퀵 슬롯 저장
	*/

	UGameOptionData* GameOption = GameInstance->GetGameOptionData();
	if(CHECK_VALID(GameOption) == false)
		return;

	int32 UserSeq = GetGameManager()->GetPlayerManager()->GetUserSeq();
	TMap<FGameplayTag, int32>& QuickSlotList = GameOption->GetSkillQuickSlotOption().SkillQuickSlotList;
	TMap<FGameplayTag, FSkillData> OwnSkills = GetSkillManager()->GetOwnSkills();

	for (auto& [Tag, Data] : OwnSkills)
	{
		if (QuickSlotList.Contains(Tag) == true)
		{
			QuickSlotList[Tag] = Data.SkillId;
		}
	}
	GameInstance->SaveGameOption();
	ApplyQuickSlotSetting();
}

void USkillSetting::ApplyQuickSlotSetting()
{
	/*
		스킬 퀵 슬롯에 세팅해놓은 걸 Status Display의 스킬 세팅으로 옮겨준다.
	*/

	UInGameMainUI* MainUI = Cast<UInGameMainUI>(GetGameManager()->GetUIManager()->GetMainUI());
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
	SaveQuickSlotData();
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