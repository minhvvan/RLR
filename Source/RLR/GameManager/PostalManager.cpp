// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/PostalManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/UIManager.h"
#include "UI/DialogueUI.h"
#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Post/PostAlertUI.h"
#include "Structs/SkillStructs.h"
#include "Components/GridPanel.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void UPostalManager::Update()
{
	OnUpdatePostalDelegateBroadcast();
}

void UPostalManager::InitializePostalManager()
{
	UUIManager* UIManager = GameInstance->GetUIManager();
	if (!UIManager) return;

	UDialogueUI* DialogueUI = UIManager->GetPage<UDialogueUI>(RLRTAG.Page_Dialogue);
	if (!DialogueUI) return;

	UPostOverlayUI* PostUI = DialogueUI->GetSubUI<UPostOverlayUI>(RLRTAG.UI_Post);

	PostUIClass = PostUI;

	if (PostUIClass)
	{
		PostUIClass->SetRecvPostData(PostRecvData);
	}
}

void UPostalManager::SetRecvPostData(const TArray<FPostResult>& NewPostResult)
{
	PostRecvData = NewPostResult;
	if (PostUIClass)
	{
		PostUIClass->SetRecvPostData(PostRecvData);
	}
}

void UPostalManager::SetSentPostData(const TArray<FPostResult>& NewPostResult)
{
	PostSentData = NewPostResult;
	if (PostUIClass)
	{
		PostUIClass->SetSentPostData(PostRecvData);
	}
}

void UPostalManager::SetAlertPostData(const FPostResult& NewPostResult)
{
	PostAlertData = NewPostResult;

	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			CreateAlertPost();
		});
}

void UPostalManager::CreateAlertPost()
{
	TSubclassOf<UPostAlertUI> PostAlertUIClass = GameInstance->GetDataManager()->GetWidgetClass<UPostAlertUI>("WBP_PostAlertUI");
	if (PostAlertUIClass)
	{
		UWorld* World = GameInstance->GetWorld();
		if (!World) return;

		// CreateWidget을 위한 적절한 World Context 제공
		UPostAlertUI* NewPostAlertUI = CreateWidget<UPostAlertUI>(World, PostAlertUIClass);
		if (!NewPostAlertUI) return;

		NewPostAlertUI->UpdatePost(PostAlertData);

		NewPostAlertUI->AddToViewport();

		if (IsValid(NewPostAlertUI))
		{
			NewPostAlertUI->UpdatePostItemSlot(PostAlertData);
		}
	}
}

const TArray<FPostResult>& UPostalManager::GetSentPostData() const
{
	return PostSentData;
}

const TArray<FPostResult>& UPostalManager::GetReceivedPostData() const
{
	return PostRecvData;
}

const FPostResult& UPostalManager::GetAlertPostData() const
{
	return PostAlertData;
}

void UPostalManager::AddToPostDeletionList(const FPostResult& PostData, bool IsSent)
{
	if (IsSent)
		SentPostDeletionList.Add(PostData);
	else
		RecvPostDeletionList.Add(PostData);
}

void UPostalManager::ClearPostDeletionList(bool IsSent)
{
	if (IsSent)
		SentPostDeletionList.Empty();
	else
		RecvPostDeletionList.Empty();
}

TArray<FPostResult> UPostalManager::GetAndClearPostDeletionList(bool IsSent)
{
	if (IsSent)
	{
		TArray<FPostResult> TempList = SentPostDeletionList;
		SentPostDeletionList.Empty();
		return TempList;
	}
	else
	{
		TArray<FPostResult> TempList = RecvPostDeletionList;
		RecvPostDeletionList.Empty();
		return TempList;
	}
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

void UPostalManager::SetItemData(int32 itemId)
{
	//ItemData[itemId] = Item;
	FItemData Data = GameInstance->GetDataManager()->GetItemData(itemId);
	ItemData[itemId] = Data;
}