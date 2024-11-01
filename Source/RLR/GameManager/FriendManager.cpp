// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/FriendManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/FriendList/FriendListUI.h"

void UFriendManager::InitializeFriendManager()
{
	UUIManager* UIManager = GameInstance->GetUIManager();
	if (!UIManager) return;

	UInGameMainUI* InGameMainUI = UIManager->GetPage<UInGameMainUI>(FGameplayTagManager::Get().Page_InGame);

	if (!InGameMainUI) return;

	UFriendListUI* FriendUI = InGameMainUI->GetFriendListUI();

	FriendListUI = FriendUI;
}

void UFriendManager::SetFriendData(const TArray<FFriendGroupResult>& NewGroupData)
{
	GroupData = NewGroupData;
	
	if (FriendListUI)
	{
		FriendListUI->SetFriendData(GroupData);
	}
}

const TArray<FFriendGroupResult>& UFriendManager::GetFriendData() const
{
	// TODO: 여기에 return 문을 삽입합니다.
	return GroupData;
}

void UFriendManager::AddToFriendDeletionList(const int32& NewFriendData)
{
}

TArray<FFriendGroupResult> UFriendManager::GetAndClearFriendDeletionList()
{
	TArray<FFriendGroupResult> TempList = FriendDeletionList;
	FriendDeletionList.Empty();
	return TempList;
}