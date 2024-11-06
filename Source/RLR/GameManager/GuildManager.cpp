// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/GuildManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/Guild/GuildUI.h"

void UGuildManager::InitializeGuildManager()
{
	UUIManager* UIManager = GameInstance->GetUIManager();
	if (!UIManager) return;

	//UInGameMainUI* InGameMainUI = Cast<UInGameMainUI>(UIManager->GetMainUI());
	//if (!InGameMainUI) return;

	//UGuildUI* GuildUI = InGameMainUI->GetGuildUI();

	//GuildOverlayUI = GuildUI;
}

void UGuildManager::SetGuildInfo(const FGuildResult& guildData)
{
	GuildData = guildData;
	
	if (GuildOverlayUI)
	{
		//GuildOverlayUI->SetGuildData(GuildData);
	}
}
