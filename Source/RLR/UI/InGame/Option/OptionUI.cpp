// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Option/OptionUI.h"

#include "UI/InGame/Option/GraphicsOption/GraphicsOption.h"
#include "UI/InGame/Option/AudioOption/AudioOption.h"
#include "UI/InGame/Option/CommunityOption/CommunityOption.h"
#include "UI/InGame/Option/GameplayOption/GameplayOption.h"
#include "UI/InGame/Option/KeyOption/KeyOption.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/OtherUserManager.h"
#include "GameManager/PlayerManager.h"

#include "Structs/PlayerStructs.h"
#include "Structs/UtilStructs.h"
#include "Structs/CommunicationStructs.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void UOptionUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	ResetButton->OnClicked.AddUniqueDynamic(this, &UOptionUI::OnClickedResetButton);
	ApplyButton->OnClicked.AddUniqueDynamic(this, &UOptionUI::OnClickedApplyButton);
	ConfirmButton->OnClicked.AddUniqueDynamic(this, &UOptionUI::OnClickedConfirmButton);
	CancelButton->OnClicked.AddUniqueDynamic(this, &UOptionUI::OnClickedCancelButton);

	//Tab
	GraphicsOptionButton->OnClicked.AddUniqueDynamic(GraphicsOption, &UGraphicsOption::OpenUI);
	AudioOptionButton->OnClicked.AddUniqueDynamic(AudioOption, &UAudioOption::OpenUI);
	CommunityOptionButton->OnClicked.AddUniqueDynamic(CommunityOption, &UCommunityOption::OpenUI);
	GameplayOptionButton->OnClicked.AddUniqueDynamic(GameplayOption, &UGameplayOption::OpenUI);
	KeyOptionButton->OnClicked.AddUniqueDynamic(KeyOption, &UKeyOption::OpenUI);
}

void UOptionUI::Init()
{
	Super::Init();
}

void UOptionUI::RefreshUI()
{
	Super::RefreshUI();
}

void UOptionUI::OpenUI()
{
	Super::OpenUI();
}

void UOptionUI::Clear()
{
	Super::Clear();
}

void UOptionUI::CloseUI()
{
	Super::CloseUI();
}

void UOptionUI::SaveGameOption()
{
	GetGameManager()->SaveGameOption();
}

void UOptionUI::LoadGameOption()
{
}

void UOptionUI::ResetGameOption()
{
}

void UOptionUI::OnClickedResetButton()
{
}

void UOptionUI::OnClickedApplyButton()
{
	KeyOption->ApplyOption();
}

void UOptionUI::OnClickedConfirmButton()
{
}

void UOptionUI::OnClickedCancelButton()
{
}

void UOptionUI::ChangeTab(OptionUI_TabType TabType)
{
	//지정된 타입을 벗어난 enum 값이 들어오면 메시지 띄운다.
	if (TabType >= OptionUI_TabType::None)
	{
		DEBUG_MESSAGE;
		return;
	}

	OptionWidgetSwitcher->SetActiveWidgetIndex((int32)TabType);
}
