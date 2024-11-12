// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RLRStruct.h"
#include "Structs/ObjectStructs.h"
#include "QuestManager.generated.h"

class UQuestListUI;

UCLASS()
class RLR_API UQuestManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void AddUserQuests(const FQuest& Quest);
	void SetUserQuests();
	const TArray<FQuest>& GetUserQuests() const { return CurrentQuests; }
	void OnQuestCompleteResponse(int32 Success);
	FQuest SelectedQuestInfo;

	/* 특정 몬스터 ID의 현재 처치 수 반환 */
	int32 GetMonsterKillCount(int32 QuestID, int32 MonsterID) const;

	/* 몬스터 처치 수 업데이트 */
	void AddMonsterKillCount(int32 QuestID, int32 MonsterID, int32 KillAmount = 1);

	/* 특정 몬스터 ID와 관련된 모든 진행 중인 퀘스트의 처치 수를 증가 */
	void AddMonsterKillCountForAllQuests(int32 MonsterID);

	/* 퀘스트 수락 시 필요한 몬스터 처치 수 초기화 */
	void InitializeQuestKillCount(int32 QuestID, const TMap<int32, int32>& RequiredMonsters);

private:
	TArray<FQuest> CurrentQuests;
	UQuestListUI* QuestListUIVariable;

private:
	void UpdateQuestUI();
	/* QuestId 별로 필요한 몬스터 처치 수 저장 <QuestId, <MonsterId, KillCount>>*/
	TMap<int32, TMap<int32, int32>> ActiveQuestMonsterKillCounts;
};
