// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildManagementUI.h"

#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"

void UGuildManagementUI::NativeConstruct()
{
	if (ChangeGuildNameButton)
	{
		ChangeGuildNameButton->OnClicked.AddDynamic(this, &UGuildManagementUI::ChangeNameButtonClicked);
	}
	if (InviteToGuildButton)
	{
		InviteToGuildButton->OnClicked.AddDynamic(this, &UGuildManagementUI::InviteButtonClicked);
	}
	if (QuitGuildButton)
	{
		QuitGuildButton->OnClicked.AddDynamic(this, &UGuildManagementUI::QuitGuldButtonClicked);
	}
}

void UGuildManagementUI::ChangeNameButtonClicked()
{
}

void UGuildManagementUI::InviteButtonClicked()
{
}

void UGuildManagementUI::QuitGuldButtonClicked()
{
}
