// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/QuestManager.h"
#include "UI/InGame/Quest/QuestUI/QuestListUI.h"
#include "UI/InGame/InGameMainUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"

void UQuestManager::SetUserQuests(const TArray<FQuest>& Quests)
{
	CurrentQuests = Quests;

	/* TODO : 인스턴스 받아오기 create widget 하는 곳 어디? */
	/*if(UQuestUI* QuestUI = )*/
}

void UQuestManager::UpdateQeustUI()
{
	/*TODO : QuestListUI->UpdateQuestList(CurrentQuests);*/
}
