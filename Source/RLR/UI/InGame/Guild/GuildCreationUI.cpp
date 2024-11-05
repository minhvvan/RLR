// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildCreationUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/GuildManager.h"
#include "GameManager/NetworkManager.h"
#include "Components/Button.h"

void UGuildCreationUI::NativeConstruct()
{
	if (CreateGuildButton)
	{
		CreateGuildButton->OnClicked.AddDynamic(this, &UGuildCreationUI::CreateGuild);
	}
}

void UGuildCreationUI::CreateGuild()
{
	/* 길드 창설 */
	GameInstance->GetNetworkManager()->SendCreateGuild();
}
