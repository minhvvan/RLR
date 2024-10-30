// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/BaseScreen.h"
#include "UI/DialogueUI.h"
#include "Components/WidgetSwitcher.h"
#include "structs/UtilStructs.h"

UWidget* UBaseScreen::GetPage(EUIType type)
{
	return WSPage->GetWidgetAtIndex((int)type);
}

EUIType UBaseScreen::GetActivePage()
{
	return (EUIType)WSPage->GetActiveWidgetIndex();
}

void UBaseScreen::SetActivePage(EUIType type)
{
	WSPage->SetActiveWidgetIndex((int)type);
}

void UBaseScreen::SetDialogueUI(TObjectPtr<UDialogueUI> newDialogueUI)
{
	auto* dialogueUI = GetPage(EUIType::DIALOGUE_PAGE);
	if (!dialogueUI) return;

	auto* test = WSPage->GetWidgetAtIndex((int)EUIType::DIALOGUE_PAGE);
}
