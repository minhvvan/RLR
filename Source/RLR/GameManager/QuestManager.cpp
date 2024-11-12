// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/QuestManager.h"
#include "UI/InGame/Quest/QuestUI/QuestListUI.h"
#include "UI/InGame/InGameMainUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "Structs/ObjectStructs.h"

void UQuestManager::AddUserQuests(const FQuest& Quest)
{
	for (const auto& need : Quest.Needs)
	{
		/* 몬스터 관련 퀘스트일 경우 */
		if (need.Key == "monster")
		{
			InitializeQuestKillCount(Quest.QuestSeq, need.Value.Map);
		}
	}

	CurrentQuests.Add(Quest);
}

void UQuestManager::SetUserQuests()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (!GM) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (!UIManager) return;

	UQuestListUI* QuestListUI = UIManager->GetSubUI<UQuestListUI>(RLRTAG.UI_Quest);
	if (!QuestListUI) return;

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
/* Monster 처치 수 반환 */
int32 UQuestManager::GetMonsterKillCount(int32 QuestID, int32 MonsterID) const
{
	if (const TMap<int32, int32>* QuestKillCounts = ActiveQuestMonsterKillCounts.Find(QuestID))
	{
		if (const int32* KillCount = QuestKillCounts->Find(MonsterID))
		{
			return *KillCount;
		}
	}
	return 0;
}
/* 퀘스트에 있는 Monster라면 Monster 처치 수 업데이트 */
void UQuestManager::AddMonsterKillCount(int32 QuestID, int32 MonsterID, int32 KillAmount)
{
	if (TMap<int32, int32>* QuestKillCounts = ActiveQuestMonsterKillCounts.Find(QuestID))
	{
		if (QuestKillCounts->Contains(MonsterID))
		{
			(*QuestKillCounts)[MonsterID] += KillAmount;
		}
	}
}
/* 특정 몬스터와 관련된 모든 퀘스트 처치 수 증가 */
void UQuestManager::AddMonsterKillCountForAllQuests(int32 MonsterID)
{
	for (auto& QuestEntry : ActiveQuestMonsterKillCounts)
	{
		int32 QuestID = QuestEntry.Key;
		TMap<int32, int32>& MonsterKillCounts = QuestEntry.Value;

		if (MonsterKillCounts.Contains(MonsterID))
		{
			MonsterKillCounts[MonsterID]++;
		}
	}
}
/* 퀘스트 수락 시 필요한 몬스터 처치 수 초기화 */
void UQuestManager::InitializeQuestKillCount(int32 QuestID, const TMap<int32, int32>& RequiredMonsters)
{
	// 몬스터 처치 수를 0으로 초기화하여 추가
	TMap<int32, int32> InitialKillCounts;
	for (const auto& MonsterRequirement : RequiredMonsters)
	{
		int32 MonsterID = MonsterRequirement.Key;
		int32 Kill = MonsterRequirement.Value;
		InitialKillCounts.Add(MonsterID, 0);
	}

	ActiveQuestMonsterKillCounts.Add(QuestID, InitialKillCounts);
}