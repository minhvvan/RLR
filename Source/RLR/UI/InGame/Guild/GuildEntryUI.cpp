// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildEntryUI.h"

#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"

void UGuildEntryUI::NativeConstruct()
{
	if (CreateGuildButton)
	{
		CreateGuildButton->OnClicked.AddDynamic(this, &UGuildEntryUI::OpenCreateGuildUI);
	}
	if (ApplyGuildButton)
	{
		ApplyGuildButton->OnClicked.AddDynamic(this, &UGuildEntryUI::OpenApplyGuildUI);
	}
}

void UGuildEntryUI::OpenApplyGuildUI()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
	}
}

void UGuildEntryUI::OpenCreateGuildUI()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(1);
	}
}