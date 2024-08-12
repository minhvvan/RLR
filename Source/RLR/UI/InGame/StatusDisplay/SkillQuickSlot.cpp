// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/StatusDisplay/SkillQuickSlot.h"

#include "Components/TextBlock.h"

#include "Player/PlayerCommands.h"
#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/GameplayTagManager.h"

void USkillQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void USkillQuickSlot::RefreshUI()
{
	Super::RefreshUI();


	URLRInputConfig* Config = GameInstance->GetDataManager()->GetInputConfig();
	if(Config)
	{ 

		FString InputString = Config->FindInputTagByActionTag(ActionTag).GetTagName().ToString();
		FString Prefix = TEXT("Input.");

		// 'Input.' 이후의 문자열을 추출
		int32 PrefixLength = Prefix.Len();
		FString AfterPrefix = InputString.Mid(PrefixLength);
	

		KeyBindingText->SetText(FText::FromString(AfterPrefix));

	}

	const FSkillData& SkillData = GetSkillData();

	if(SkillData == FSkillData::EmptySkillData)
	{
		SetSlotImage(GetDefaultSlotImage());
		return;
	}

	SetSlotImage(SkillData.SkillImage);

	/*
		연동된 단축키를 찾아주자.
	*/

	
	//KeyBindingText->SetText()
}

void USkillQuickSlot::Clear()
{
	Super::Clear();
}

void USkillQuickSlot::UpdatedSkillAttack()
{
	if(IsEmpty() == true)
		return;
	

	FText DebugText = FText::Format(FText::FromString("Update Skill Attack {0}"), FText::FromString(GetSkillData().Name));
	Util::DebugLog(DebugText.ToString());
}

void USkillQuickSlot::SetActionTag(FGameplayTag NewActionTag)
{
	ActionTag = NewActionTag;
}
