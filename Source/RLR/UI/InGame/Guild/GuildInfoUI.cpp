// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildInfoUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/GuildManager.h"

#include "Components/TextBlock.h"

void UGuildInfoUI::NativeConstruct()
{
	FGuildResult guild = GameInstance->GetGuildManager()->GetGuildInfo();
	guildMemberCount = guild.GuildRanks.Num();

	if (GuildLevelText)
	{
		GuildLevelText->SetText(FText::AsNumber(guild.guildLevel));
	}
	if (GuildRankText)
	{

	}
	if (GuildCreatedDateText)
	{

	}
	if (GuildMasterNameText)
	{

	}
	if (GuildMemberCountText)
	{
		GuildMemberCountText->SetText(FText::AsNumber(guildMemberCount));
	}
	if (GuildMaxUserText)
	{
		GuildMaxUserText->SetText(FText::AsNumber(guild.guildMaxUser));
	}
	if (GuildPointText)
	{

	}
}

void UGuildInfoUI::RefreshUI()
{
	FGuildResult guild = GameInstance->GetGuildManager()->GetGuildInfo();
	guildMemberCount = guild.GuildRanks.Num();

	GuildLevelText->SetText(FText::AsNumber(guild.guildLevel));
	GuildMemberCountText->SetText(FText::AsNumber(guildMemberCount));
	GuildMaxUserText->SetText(FText::AsNumber(guild.guildMaxUser));
}
