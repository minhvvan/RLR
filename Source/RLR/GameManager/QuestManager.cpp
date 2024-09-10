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

UQuestListUI* UQuestManager::GetQuestListUI() const
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (!GM) return nullptr;

	UUIManager* UIManager = GM->GetUIManager();
	if (!UIManager) return nullptr;

	UInGameMainUI* InGameMainUI = Cast<UInGameMainUI>(UIManager->GetMainUI());
	if (!InGameMainUI) return nullptr;

	return InGameMainUI->GetQuestListUI();
}

void UQuestManager::UpdateQuestUI()
{
	/*TODO : QuestListUI->UpdateQuestList(CurrentQuests);*/

	UQuestListUI* QuestListUI = GetQuestListUI();
	if (QuestListUI)
	{
		QuestListUI->UpdateQuestList(CurrentQuests);
	}
}

void UQuestManager::OnQuestCompleteResponse(int32 Success)
{
	if (Success != 0)
	{
		UQuestListUI* QuestListUI = GetQuestListUI();
		if (QuestListUI)
		{
			QuestListUI->RemoveCompletedQuest(SelectedQuestSeq);
		}
	}
}