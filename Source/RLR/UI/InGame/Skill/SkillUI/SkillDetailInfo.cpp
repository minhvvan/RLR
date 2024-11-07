// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillDetailInfo.h"
#include "UI/InGame/Skill/SkillUI/SkillTree/SkillUpgrade.h"
#include "UI/InGame/InGameMainUI.h"


#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Structs/SkillStructs.h"
#include "Structs/UtilStructs.h"

void USkillDetailInfo::NativeConstruct()
{
	Super::NativeConstruct();

	UpgradeSkillButton->OnClicked.AddUniqueDynamic(this, &USkillDetailInfo::OnClickedUpgradeSkillButton);
	ShowChainSkillButton->OnClicked.AddUniqueDynamic(this, &USkillDetailInfo::OnClickedShowChainSkillButton);

}

void USkillDetailInfo::RefreshUI()
{
	Super::RefreshUI();

	if (SkillData == FSkillData::EmptySkillData)
	{
		Clear();
		return;
	}

	if (ActionResource == FActionResource::EmptyActionResource)
	{
		Clear();
		return;
	}

	SetVisibility(ESlateVisibility::Visible);


	/*
	* TODO
		지금은 스킬 이미지를 띄워주고 있지만, 나중에는 미리보기 영상이 나오게 해주기
	*/

	SkillNameText->SetText(SkillData.Name);

	FString SkillInfoString = SkillData.ToString();
	SkillInfoText->SetText(FText::FromString(SkillInfoString));


	UTexture2D* Texture = ActionResource.ActionImage;
	if (IsValid(Texture) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("USkillDetailInfo::RefreshUI Error. 스킬 이미지 정보가 없습니다."));
	}

	SkillImage->SetBrushFromTexture(Texture, true);
}

void USkillDetailInfo::Clear()
{
	

}

void USkillDetailInfo::OnClickedUpgradeSkillButton()
{
	if (SkillData == FSkillData::EmptySkillData)
	{
		FGameplayTagManager TagManager = FGameplayTagManager::Get();
		GameInstance->GetUIManager()->CloseSubUI(TagManager.UI_Skill_Upgrade);
		return;
	}

	GameInstance->GetUIManager()->ToggleSubUI(FGameplayTagManager::Get().UI_Skill_Upgrade);
}

void USkillDetailInfo::OnClickedShowChainSkillButton()
{
	Util::DebugLog(TEXT("OnClickedShowChainSkillButton"));

	/*
		연계 스킬을 보여준다.
	*/
}

void USkillDetailInfo::SetSkillData(FSkillData NewSkillData)
{

	//만약 스킬 정보가 비어 있다면 그냥 비워준다.
	if (NewSkillData == FSkillData::EmptySkillData)
	{
		Clear();
		return;
	}
		

	SkillData = NewSkillData;
	RefreshUI();
}
