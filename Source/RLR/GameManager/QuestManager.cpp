// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/QuestManager.h"
#include "UI/InGame/Quest/QuestUI/QuestListUI.h"
#include "UI/InGame/InGameMainUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "Structs/ObjectStructs.h"
void UQuestManager::AddUserQuests(const FQuest& Quest)
{
	CurrentQuests.Add(Quest);
}
void UQuestManager::SetUserQuests()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (!GM) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (!UIManager) return;

	UInGameMainUI* InGameMainUI = Cast<UInGameMainUI>(UIManager->GetMainUI());
	if (!InGameMainUI) return;

	UQuestListUI* QuestListUI = InGameMainUI->GetQuestListUI();
	/* TODO : 일단 변수에 저장하는 것으로 바꿨는데, 서버연결 해서 확인해야함 */
	QuestListUIVariable = QuestListUI;

	UpdateQuestUI();
}

void UQuestManager::UpdateQuestUI()
{
	if (QuestListUIVariable)
	{
		QuestListUIVariable->UpdateQuestList(CurrentQuests);
	}
}

void UQuestManager::OnQuestCompleteResponse(int32 Success)
{
	if (Success)
	{
		if (QuestListUIVariable)
		{
			QuestListUIVariable->RemoveCompletedQuest(SelectedQuestInfo);
		}
	}
}