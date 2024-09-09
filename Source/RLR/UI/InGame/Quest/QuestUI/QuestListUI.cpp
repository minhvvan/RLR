// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Quest/QuestUI/QuestListUI.h"

void UQuestListUI::NativeConstruct()
{
	Super::NativeConstruct();
	SetUIType(EUIType::QUEST);
	SetUITag(FGameplayTagManager::Get().UI_Quest);
}

void UQuestListUI::UpdateQuestList(const TArray<FQuest>& Quests)
{
	/* TODO : 퀘스트 목록 구성 로직 */
}