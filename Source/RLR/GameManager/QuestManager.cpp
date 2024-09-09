// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/QuestManager.h"
#include "UI/InGame/Quest/QuestUI/QuestListUI.h"
#include "UI/InGame/InGameMainUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "Structs/ObjectStructs.h"

void UQuestManager::SetUserQuests(const TArray<FQuest>& Quests)
{
	CurrentQuests = Quests;

	UpdateQuestUI();
}

void UQuestManager::UpdateQuestUI()
{
	/*TODO : QuestListUI->UpdateQuestList(CurrentQuests);*/
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if(!GM) return;

	UUIManager* UIManager = GM->GetUIManager();
	if(!UIManager) return;

	UInGameMainUI* InGameMainUI = Cast<UInGameMainUI>(UIManager->GetMainUI());
	if(!InGameMainUI) return;

	UQuestListUI* QuestListUI = InGameMainUI->GetQuestListUI();
	if (QuestListUI)
	{
		QuestListUI->UpdateQuestList(CurrentQuests);
	}
}
