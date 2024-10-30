// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/BaseScreen.h"
#include "UI/DialogueUI.h"
#include "Components/WidgetSwitcher.h"
#include "UI/Components/PageSwitcher.h"
#include "structs/UtilStructs.h"

UWidget* UBaseScreen::GetPage(EUIType type)
{
	return PageSwitcher->GetWidgetAtIndex((int)type);
}

EUIType UBaseScreen::GetActivePage()
{
	return (EUIType)PageSwitcher->GetActiveWidgetIndex();
}

void UBaseScreen::SetActivePage(EUIType type)
{
	PageSwitcher->SetActiveWidgetIndex((int)type);
}

void UBaseScreen::SetDialogueUI(TObjectPtr<UDialogueUI> newDialogueUI)
{
	PageSwitcher->SetWidgetAtIndex((int)EUIType::DIALOGUE_PAGE, newDialogueUI);
}