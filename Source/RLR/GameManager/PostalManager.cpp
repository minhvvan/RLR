// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/PostalManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/Post/PostOverlayUI.h"
#include "Structs/SkillStructs.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void UPostalManager::Update()
{
	OnUpdatePostalDelegateBroadcast();
}

void UPostalManager::SetPostData(const TArray<FPostResult>& NewPostResult)
{
	PostResultData = NewPostResult;
	// 확인
	ClassifyPostData();

	UUIManager* UIManager = GameInstance->GetUIManager();
	if (!UIManager) return;

	UInGameMainUI* InGameMainUI = Cast<UInGameMainUI>(UIManager->GetMainUI());
	if (!InGameMainUI) return;

	UPostOverlayUI* PostUI = InGameMainUI->GetPostOverlayUI();

	PostUIClass = PostUI;

	if (PostUIClass)
	{
		PostUIClass->SetPostResults(NewPostResult);
	}

}
const TArray<FPostResult>& UPostalManager::GetPostData() const
{
	return PostResultData;
}

const TArray<FPostResult>& UPostalManager::GetSentPosts() const
{
	return SentPostList;
}

const TArray<FPostResult>& UPostalManager::GetReceivedPosts() const
{
	return ReceivedPostList;
}

void UPostalManager::OnUpdatePostalDelegateBroadcast()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			// 유효성 검사 추가
			if (!IsValid(this))
			{
				DEBUG_MESSAGE;
				return;
			}
			OnUpdatePostalDelegate.Broadcast();
		});
}

void UPostalManager::SetItemData(int32 itemId, FItemData Item)
{
	ItemData[itemId] = Item;
}

void UPostalManager::ClassifyPostData()
{
    SentPostList.Empty();
    ReceivedPostList.Empty();

    // 사용자 시퀀스 얻기
    int64 UserSeq = GameInstance->GetNetworkManager()->GetUserSeq();

    for (const FPostResult& PostData : PostResultData)
    {
        if (PostData.SenderSeq == UserSeq)
        {
            SentPostList.Add(PostData);
        }
        else if (PostData.ReceiverSeq == UserSeq)
        {
            ReceivedPostList.Add(PostData);
        }
    }
}