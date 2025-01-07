// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/GuildManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/Guild/GuildUI.h"
#include "UI/InGame/Guild/PlayerGuildUI.h"
#include "Components/WidgetSwitcher.h"


void UGuildManager::SetGuildInfo(const FGuildResult& guildData)
{
	GuildData = guildData;

	/* TODO : 길드원탭에 길드원 버튼 동적생성하기 */
	for (const FGuildRank& guildRank : GuildData.GuildRanks)
	{
		if (guildRank.UserSeq == GameInstance->GetUserSeq())
		{
			CurrentUserRole = guildRank.GuildRankSeq;
			break;
		}
	}

	/* 길드에 속하지 않았다면 */
    AsyncTask(ENamedThreads::GameThread, [this]()
        {
            if (GuildOverlayUI && GuildOverlayUI->WidgetSwitcher)
            {
				if (GuildData.guildSeq != 0)
				{
					GuildOverlayUI->WidgetSwitcher->SetActiveWidgetIndex(1);
					if (GuildOverlayUI->PlayerGuildUI)
					{
						GuildOverlayUI->PlayerGuildUI->RefreshUI();
					}
				}
				else
				{
					GuildOverlayUI->WidgetSwitcher->SetActiveWidgetIndex(0);
				}
            }
        });
}

FGuildResult UGuildManager::GetGuildInfo()
{
	return GuildData;
}

void UGuildManager::SetGuildQuestData(const TArray<FGuildQuest>& NewGuildQuestData)
{
	GuildQuestData.Empty();
	
	for (const FQuest& GuildQuestDatum : NewGuildQuestData)
	{
		GuildQuestData.Add(GuildQuestDatum);
	}
}

TArray<FGuildQuest> UGuildManager::GetGuildQuestData()
{
	return GuildQuestData;
}

bool UGuildManager::HasPermission(EGuildRole Role)
{
	return CurrentUserRole == Role;
}