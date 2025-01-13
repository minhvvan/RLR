// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/Quest/GuildQuestCardUI.h"
#include "Components/Border.h"

void UGuildQuestCardUI::NativeConstruct()
{
}

void UGuildQuestCardUI::SetColorAsQuestType(FGuildQuest NewGuildQuestDatum)
{
	GuildQuestDatum = NewGuildQuestDatum;
	EGuildQuestType guildQuestType = GuildQuestDatum.GuildQuestType;
	switch (guildQuestType)
	{
	case EGuildQuestType::Normal:
		Border->SetBrushColor(FLinearColor(0.572f, 0.373f, 0.216f, 1.0f));
		break;
	case EGuildQuestType::Dungeon:
		Border->SetBrushColor(FLinearColor(0.620f, 0.847f, 0.631f, 1.0f));
		break;
	case EGuildQuestType::Raid:
		Border->SetBrushColor(FLinearColor(0.247f, 0.882f, 1.0f, 1.0f));
		break;
	default:
		Border->SetBrushColor(FLinearColor::White);
		break;
	}
}

FGuildQuest UGuildQuestCardUI::GetGuildQuestData()
{
	return GuildQuestDatum;
}