// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/InGameMenu/InGameMenuUI.h"
#include "UI/InGame/InGameMenu/InGameMenuTab.h"
#include "UI/InGame/InGameMenu/InGameMenuTabList.h"
#include "UI/InGame/InGameMenu/InGameMenuTabListElement.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "Structs/UtilStructs.h"

void UInGameMenuUI::NativeConstruct()
{
	Super::NativeConstruct();
	SetUIType(EUIType::INGAMEMENU);

	if (IsValid(CheckUnhoveredButton))
	{
		CheckUnhoveredButton->OnUnhovered.AddUniqueDynamic(this, &UInGameMenuUI::OnUnhovered);
	}
}
void UInGameMenuUI::AddTab()
{

	/*
		Option
	*/
	AddTabListElement(OptionTab, OptionTabText, OptionTab_GameMenuText, &UInGameMenuUI::OnClickedGameMenu);
	AddTabListElement(OptionTab, OptionTabText, OptionTab_CustomerServiceCenter, &UInGameMenuUI::OnClickedCustomerService);
	AddTabListElement(OptionTab, OptionTabText, OptionTab_EscapeText, &UInGameMenuUI::OnClickedEscape);


	AddTabListElement(GuidTab, GuidTabText, TestText, &UInGameMenuUI::OnTest);
	AddTabListElement(GuidTab, GuidTabText, TestText, &UInGameMenuUI::OnTest);
	AddTabListElement(GuidTab, GuidTabText, TestText, &UInGameMenuUI::OnTest);
}

void UInGameMenuUI::OnClickedGameMenu()
{
	UUtilBlueprintFunctionLibrary::DebugLog(TEXT("OnClickedGameMenu"));
}

void UInGameMenuUI::OnClickedCustomerService()
{
	UUtilBlueprintFunctionLibrary::DebugLog(TEXT("OnClickedCustomerService"));
}

void UInGameMenuUI::OnClickedEscape()
{
	UUtilBlueprintFunctionLibrary::DebugLog(TEXT("OnClickedEscape"));
}

void UInGameMenuUI::OnTest()
{
	UUtilBlueprintFunctionLibrary::DebugLog(TEXT("아직 준비 중입니다."));
}


void UInGameMenuUI::AddTabListElement(UInGameMenuTab* MenuTab, FText MenuTabName, FText ElementName, TFunction<void(UInGameMenuUI*)> StoredFunction)
{
	TabList.AddUnique(MenuTab);

	MenuTab->SetTabText(MenuTabName);
	MenuTab->InGameMenuUI = this;

	UInGameMenuTabListElement* Element = NewObject<UInGameMenuTabListElement>(this);
	Element->ElementText =ElementName;
	Element->ButtonClickedFunc = StoredFunction;
	Element->InGameMenuUI = this;

	MenuTab->InGameMenuTabList->MenuTabListView->AddItem(Element);
}

void UInGameMenuUI::CloseAllTabList()
{
	for (UInGameMenuTab* Tab : TabList)
	{
		Tab->InGameMenuTabList->Close();
	}

}

void UInGameMenuUI::OnUnhovered()
{
	CloseAllTabList();
}

