// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildMember.h"

#include "Components/TextBlock.h"

void UGuildMember::NativeConstruct()
{
	Super::NativeConstruct();

	if (GuildRankText)
	{
		GuildRankText->SetText(FText::FromString(GetGuildRankText(guildMember.GuildRankSeq)));
	}
	if (GuildReputation)
	{
		GuildReputation->SetText(FText::AsNumber(guildMember.guildReputation));
	}
	if (CurrentLocation)
	{
		// TODO : Player 현재 위치 표기
	}
	if (OnlineStatusText)
	{
		// TODO : Player Online 상태 표기
	}
}

FString UGuildMember::GetGuildRankText(EGuildRole Rank)
{
	switch (Rank)
	{
	case EGuildRole::MASTER:
		return TEXT("MASTER");
	case EGuildRole::VICEMASTER:
		return TEXT("VICEMASTER");
	case EGuildRole::OFFICER:
		return TEXT("OFFICER");
	case EGuildRole::MEMBER:
		return TEXT("MEMBER");
	default:
		return TEXT("NONE");
	}
}
