// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/Shop/GuildShopTabWidget.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void UGuildShopTabWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
	}
	if (GuildShopButton)
	{
		GuildShopButton->OnClicked.AddUniqueDynamic(this, &UGuildShopTabWidget::SwitchToPersonalShop);
	}
	if (PersonalShopButton)
	{
		PersonalShopButton->OnClicked.AddUniqueDynamic(this, &UGuildShopTabWidget::SwitchToGuildShop);
	}
}

void UGuildShopTabWidget::RefreshUI()
{
	WidgetSwitcher->SetActiveWidgetIndex(0);
}

void UGuildShopTabWidget::SwitchToPersonalShop()
{
	WidgetSwitcher->SetActiveWidgetIndex(0);
}

void UGuildShopTabWidget::SwitchToGuildShop()
{
	WidgetSwitcher->SetActiveWidgetIndex(1);
}