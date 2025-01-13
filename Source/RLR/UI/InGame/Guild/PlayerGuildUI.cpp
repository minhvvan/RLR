// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/PlayerGuildUI.h"
#include "UI/InGame/Guild/Quest/GuildQuestUI.h"
#include "UI/InGame/Guild/Shop/GuildShopTabWidget.h"
#include "UI/InGame/Guild/ActivityLog/GuildActivityLogUI.h"
#include "UI/InGame/Guild/GuildReportAndExitUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"

void UPlayerGuildUI::NativeConstruct()
{
	bOpenGuildReport = false;
	if (GuildReportAndExitUI)
	{
		GuildReportAndExitUI->PlayerGuildUI = this;
	}
	if (GuildMainButton)
	{
		GuildMainButton->OnClicked.AddUniqueDynamic(this, &UPlayerGuildUI::SwitchToGuildMainUI);
	}
	if (GuildQuestButton)
	{
		GuildQuestButton->OnClicked.AddUniqueDynamic(this, &UPlayerGuildUI::SwitchToGuildQuestUI);
	}
	if (GuildShopButton)
	{
		GuildShopButton->OnClicked.AddUniqueDynamic(this, &UPlayerGuildUI::SwitchToGuildShopUI);
	}
	if (GuildActivityLogButton)
	{
		GuildActivityLogButton->OnClicked.AddUniqueDynamic(this, &UPlayerGuildUI::SwitchToGuildActivityLogUI);
	}
	if (GuildMemberButton)
	{
		GuildMemberButton->OnClicked.AddUniqueDynamic(this, &UPlayerGuildUI::SwitchToGuildMember);
	}
	if (GuildManageButton)
	{
		GuildManageButton->OnClicked.AddUniqueDynamic(this, &UPlayerGuildUI::SwitchToGuildManagement);
	}
	if (CloseButton)
	{
		CloseButton->OnClicked.AddUniqueDynamic(this, &UPlayerGuildUI::CloseGuildWidget);
	}
	if (GuildReportButton)
	{
		GuildReportButton->OnClicked.AddUniqueDynamic(this, &UPlayerGuildUI::OpenGuildReportUI);
	}
}

void UPlayerGuildUI::RefreshUI()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
	}
}

void UPlayerGuildUI::SwitchToGuildMainUI()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
		if (GuildMainUI)
		{

		}
	}
}

void UPlayerGuildUI::SwitchToGuildQuestUI()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(1);
		if (GuildQuestUI)
		{
			GuildQuestUI->RefreshUI();
		}
	}
}

void UPlayerGuildUI::SwitchToGuildShopUI()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(2);
		if (GuildShopTabWidget)
		{
			GuildShopTabWidget->RefreshUI();
		}
	}
}

void UPlayerGuildUI::SwitchToGuildActivityLogUI()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(3);
		if (GuildActivityLogUI)
		{
			GuildActivityLogUI->RefreshUI();
		}
	}
}

void UPlayerGuildUI::SwitchToGuildMember()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(4);
		if (GuildMemberUI)
		{

		}
	}
}

void UPlayerGuildUI::SwitchToGuildManagement()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(5);
		if (GuildManagementUI)
		{

		}
	}
}

void UPlayerGuildUI::CloseGuildWidget()
{
	CloseGuildButtonCLicked.Broadcast();
}

void UPlayerGuildUI::OpenGuildReportUI()
{
	if (bOpenGuildReport)
	{
		bOpenGuildReport = false;
		GuildReportAndExitUI->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		bOpenGuildReport = true;
		GuildReportAndExitUI->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPlayerGuildUI::SetGuildOpenState(bool bOpenState)
{
	bOpenGuildReport = bOpenState;
}