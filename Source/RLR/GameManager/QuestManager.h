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
	void SetUserQuests(const TArray<FQuest>& Quests);
	const TArray<FQuest>& GetUserQuests() const { return CurrentQuests; }
	void OnQuestCompleteResponse(int32 Success);
	FQuest SelectedQuestInfo;

private:
	TArray<FQuest> CurrentQuests;
	UQuestListUI* GetQuestListUI() const;

private:
	void UpdateQuestUI();
};
