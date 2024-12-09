
// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/UIManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/LiteralManager.h"
#include "GameManager/RLRStruct.h"
#include "Components/PanelWidget.h"
#include "Components/SizeBox.h"
#include "UI/MainUI.h"
#include "UI/SubUI.h"
#include "UI/SlotUI.h"
#include "UI/DialogueUI.h"
#include "UI/LoadingScreen/LoadingScreen.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Structs/ItemStructs.h"
#include "RLR.h"

void UUIManager::OpenMainUI(TSubclassOf<UBaseUI> UIClass)
{
	MainUI = CreateWidget<UMainUI>(GetWorld(), UIClass);
	if (!MainUI) return;

	MainUI->AddToViewport();
	MainUI->SetInputMode();

	UpdatedPartyPlayerInfo.Clear();
	UpdatedPlayerInfo.Clear();

	FString CurrentLevelName = GetWorld()->GetMapName();
	if (CurrentLevelName.Contains(RLRLITERAL.LevelName_Main))
	{
		// UI가 완전히 로드된 후에만 네트워크 패킷 처리
		if (GameInstance)
		{
			GameInstance->GetNetworkManager()->SendServerRequest();
			GameInstance->GetNetworkManager()->SendUserQuestPacket();
			GameInstance->GetNetworkManager()->SendInventoryPacket();
		}
	}
}

void UUIManager::ToggleSubUI(FGameplayTag UITag)
{
	//UI Toggle
	UMainUI* currentMainUI = GetPage<UMainUI>(FGameplayTagManager::Get().Page_InGame);
	if (!currentMainUI) return;

	currentMainUI->ToggleSubUI(UITag);
}

USubUI* UUIManager::OpenSubUI(FGameplayTag UITag)
{
	UMainUI* currentMainUI = GetPage(GetActivePageTag());
	if (!currentMainUI) return nullptr;

	return currentMainUI->OpenSubUI(UITag);
}

void UUIManager::CloseSubUI(FGameplayTag UITag)
{
	auto currentMainUI = GetPage<UMainUI>(GetActivePageTag());
	if (!currentMainUI) return;

	currentMainUI->CloseSubUI(UITag);
}

FGameplayTag UUIManager::GetActivePageTag()
{
	UBaseScreen* BaseScreen = Cast<UBaseScreen>(MainUI);
	if (!BaseScreen) return FGameplayTag::EmptyTag;
	return BaseScreen->GetActivePageTag();
}

void UUIManager::ClosePage()
{
	UBaseScreen* BaseScreen = Cast<UBaseScreen>(MainUI);
	if (!BaseScreen) return;

	BaseScreen->SetActivePage(FGameplayTagManager::Get().Page_InGame);
}