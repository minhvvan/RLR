// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/InGameMainUI.h"
#include "UI/SubUI.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/InGame/CharacterStatus/Equipment/EquipmentUI.h"
#include "UI/InGame/Inventory/ItemInformation.h"
#include "Blueprint/WidgetTree.h"
#include "RLR.h"

void UInGameMainUI::NativeConstruct()
{
	Super::NativeConstruct();

	UserActionSubUI.Add(InventoryUI.Get());
	//UserActionSubUI.Add(EquipmentUI.Get());
	UserActionSubUI.Add(ItemInformation.Get());
	RLR_LOG(LogRLR, Log, TEXT("NativeConstruct"));
}

bool UInGameMainUI::ToggleSubUI(int inputID)
{
	if(!UserActionSubUI.IsValidIndex(inputID)) return false;

	bool bOpen = UserActionSubUI[inputID]->GetVisibility() == ESlateVisibility::Hidden;

	if (bOpen)
	{
		UserActionSubUI[inputID]->OpenUI();
	}
	else
	{
		UserActionSubUI[inputID]->CloseUI();
	}

	return bOpen;
}

USubUI* UInGameMainUI::GetSubUI(int inputID)
{
	if (!UserActionSubUI.IsValidIndex(inputID)) return nullptr;
	return UserActionSubUI[inputID];
}
