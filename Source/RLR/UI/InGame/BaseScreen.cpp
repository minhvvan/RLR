// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/BaseScreen.h"
#include "Components/WidgetSwitcher.h"

UWidget* UBaseScreen::GetPage(EUIType type)
{
	return WSPage->GetActiveWidget();
}

EUIType UBaseScreen::GetActivePage()
{
	return (EUIType)WSPage->GetActiveWidgetIndex();
}

void UBaseScreen::SetActivePage(EUIType type)
{
	WSPage->SetActiveWidgetIndex((int)type);
}
