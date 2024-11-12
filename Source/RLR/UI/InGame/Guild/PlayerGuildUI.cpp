// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/PlayerGuildUI.h"
#include "UI/InGame/Guild/GuildReportAndExitUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"

void UPlayerGuildUI::NativeConstruct()
{
	GuildReportAndExitUI->PlayerGuildUI = this;

	if (GuildMainButton)
	{
		GuildMainButton->OnClicked.AddDynamic(this, &UPlayerGuildUI::SwitchToGuildInfo);
	}
	if (GuildMemberButton)
	{
		GuildMemberButton->OnClicked.AddDynamic(this, &UPlayerGuildUI::SwitchToGuildMember);
	}
	if (ManageGuildButton)
	{
		ManageGuildButton->OnClicked.AddDynamic(this, &UPlayerGuildUI::SwitchToGuildManagement);
	}
	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UPlayerGuildUI::CloseGuildWidget);
	}
	if (GuildReportButton)
	{
		GuildReportButton->OnClicked.AddDynamic(this, &UPlayerGuildUI::OpenGuildReportUI);
	}
}

void UPlayerGuildUI::SwitchToGuildInfo()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
		if (GuildMainUI)
		{

		}
	}
}

void UPlayerGuildUI::SwitchToGuildMember()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(1);
		if (GuildMemberUI)
		{

		}
	}
}

void UPlayerGuildUI::SwitchToGuildManagement()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(2);
		if (GuildManagementUI)
		{

		}
	}
}

void UPlayerGuildUI::CloseGuildWidget()
{
	/* 민환님께서 바꾸신 버전으로 적용하기 */
	//CloseUI(FGameplayTagManager::Get().Action_Default_GuildOpen);
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