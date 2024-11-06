// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/PlayerGuildUI.h"

#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"

void UPlayerGuildUI::NativeConstruct()
{
	if (GuildInfoButton)
	{
		GuildInfoButton->OnClicked.AddDynamic(this, &UPlayerGuildUI::SwitchToGuildInfo);
	}
	if (GuildMemberButton)
	{
		GuildMemberButton->OnClicked.AddDynamic(this, &UPlayerGuildUI::SwitchToGuildMember);
	}
	if (ManageGuildButton)
	{
		ManageGuildButton->OnClicked.AddDynamic(this, &UPlayerGuildUI::SwitchToGuildManagement);
	}
}

void UPlayerGuildUI::SwitchToGuildInfo()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
		if (GuildInfoUI)
		{

		}
	}
}

void UPlayerGuildUI::SwitchToGuildMember()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
		if (GuildMemberUI)
		{

		}
	}
}

void UPlayerGuildUI::SwitchToGuildManagement()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
		if (GuildManagementUI)
		{

		}
	}
}
