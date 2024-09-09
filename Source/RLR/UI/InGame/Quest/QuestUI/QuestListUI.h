// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/UtilStructs.h"
#include "UI/SubUI.h"
#include "QuestListUI.generated.h"

UCLASS()
class RLR_API UQuestListUI : public USubUI
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct();

public:
	void UpdateQuestList(const TArray<FQuest>& Quests);
};
