// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Subsystems/GameInstanceSubsystem.h"
#include "RLRStruct.h"
#include "QuestManager.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UQuestManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void SetUserQuests(const TArray<FQuest>& Quests);
	const TArray<FQuest>& GetUseerQuests() const { return CurrentQuests; }

private:
	TArray<FQuest> CurrentQuests;

private:
	void UpdateQeustUI();
};
