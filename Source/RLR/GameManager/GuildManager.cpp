// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/GuildManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/Guild/GuildUI.h"
#include "Components/WidgetSwitcher.h"


void UGuildManager::SetGuildInfo(const FGuildResult& guildData)
{
	GuildData = guildData;

	/* 길드에 속하지 않았다면 */
    AsyncTask(ENamedThreads::GameThread, [this]()
        {
            if (GuildOverlayUI && GuildOverlayUI->WidgetSwitcher)
            {
				if (GuildData.guildSeq != -1)
				{
					GuildOverlayUI->WidgetSwitcher->SetActiveWidgetIndex(1);
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