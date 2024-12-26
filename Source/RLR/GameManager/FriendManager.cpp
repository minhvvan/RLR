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

	UFriendListUI* FriendUI = UIManager->GetSubUI<UFriendListUI>(RLRTAG.Action_Default_FriendOpen);
	if (!FriendUI) return;

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

void UFriendManager::SetRequestFriendData(int NewFriendSeq, FString NewFriendName)
{
	RequestFriendData.Add(NewFriendSeq) = NewFriendName;
	if (FriendListUI)
	{
		FriendListUI->SetFriendRequestData(RequestFriendData);
		FriendListUI->SetFriendRequestMessageBox(NewFriendName);
	}
}

const TMap<int32, FString>& UFriendManager::GetRequestFriendData() const
{
	return RequestFriendData;
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

void UFriendManager::DeleteFromRequestList(int friendSeq)
{
	RequestFriendData.Remove(friendSeq);
}
void UFriendManager::SetFriendMemo(int32 FriendSeq, const FString& Memo)
{
	if (FriendMemoMap.Contains(FriendSeq))
	{
		FriendMemoMap[FriendSeq] = Memo;
	}
	else
	{
		FriendMemoMap.Add(FriendSeq, Memo);
	}
}

FString UFriendManager::GetFriendMemo(int32 FriendSeq) const
{
	if (FriendMemoMap.Contains(FriendSeq))
	{
		return FriendMemoMap[FriendSeq];
	}
	return FString();
}
