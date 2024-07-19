// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/InGameMainUI.h"
#include "UI/SubUI.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/InGame/CharacterStatus/CharacterStatusUI.h"
#include "UI/InGame/Inventory/ItemInformation.h"
#include "Blueprint/WidgetTree.h"
#include "RLR.h"

void UInGameMainUI::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UInGameMainUI::ToggleSubUI(int inputID)
{
	EUIType inputKey = (EUIType)inputID;
	if (!UserActionSubUI.Find(inputKey)) return false;

	bool bOpen = UserActionSubUI[inputKey]->GetVisibility() == ESlateVisibility::Hidden;

	if (bOpen)
	{
		UserActionSubUI[inputKey]->OpenUI();
	}
	else
	{
		UserActionSubUI[inputKey]->CloseUI();
	}

	return bOpen;
}

USubUI* UInGameMainUI::GetSubUI(int inputID)
{
	EUIType inputKey = static_cast<EUIType>(inputID);

	if (!UserActionSubUI.Contains(inputKey)) return nullptr;
	return UserActionSubUI[inputKey];
}
