// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Post/PostTabWidget.h"
#include "UI/InGame/Post/PostWriteTabWidget.h"
#include "UI/InGame/Post/PostSentTabWidget.h"
#include "UI/InGame/Post/PostReceivedTabWidget.h"
#include "UI/InGame/Post/InputTransactionCost.h"
#include "GameManager/PostalManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "Structs/UtilStructs.h"
#include "Components/GridPanel.h"
#include "Components/EditableTextBox.h"
#include "Components/MultiLineEditableText.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void UPostOverlayUI::NativeConstruct()
{
	Super::NativeConstruct();

	SetUIType(EUIType::POST_UI);
	SetUITag(FGameplayTagManager::Get().UI_Post);

	if (ReceivedPostButton)
		ReceivedPostButton->OnClicked.AddDynamic(this, &UPostOverlayUI::OnReceivedPostButtonClicked);
	if (SentPostButton)
		SentPostButton->OnClicked.AddDynamic(this, &UPostOverlayUI::OnSentPostButtonClicked);
	if (WritePostButton)
		WritePostButton->OnClicked.AddDynamic(this, &UPostOverlayUI::OnWritePostButtonClicked);
}

void UPostOverlayUI::Init()
{
	auto dataManager = GameInstance->GetDataManager();
	if (!dataManager) return;

	TSubclassOf<UPostItemSlot> PostItemSlotClass = dataManager->GetWidgetClass<UPostItemSlot>("WBP_PostItemSlot");
	
	PostWriteTabWidget->PostSlotList.Empty();
	PostWriteTabWidget->PostSlotList.Init(nullptr, MaxPostSlotCount);

	if (PostItemSlotClass == nullptr)
	{
		DEBUG_MESSAGE;
		return;
	}

	for (int32 Count = 0; Count < MaxPostSlotCount; Count++)
	{
		UPostItemSlot* NewSlot = CreateWidget<UPostItemSlot>(this, PostItemSlotClass);
		PostWriteTabWidget->PostSlotList[Count] = NewSlot;
		NewSlot->SlotIndex = Count;
		NewSlot->PostUI = this;

		PostWriteTabWidget->PostSlotGridPanel->AddChildToGrid(NewSlot, 0, Count);
	}
}

void UPostOverlayUI::RefreshUI()
{
	// 서버나 캐시에서 새 우편 데이터 가져오기
	TArray<FPostResult> NewPostData = GameInstance->GetPostalManager()->GetPostData();
	SetPostResults(NewPostData);
	UpdatePostWidget();
}

void UPostOverlayUI::OnReceivedPostButtonClicked()
{
	if (PostWidgetSwitcher)
	{
		PostWidgetSwitcher->SetActiveWidgetIndex(0);

		AsyncTask(ENamedThreads::GameThread, [this]()
			{
				UpdatePostWidget();
			});
	}
}

void UPostOverlayUI::OnSentPostButtonClicked()
{
	if (PostWidgetSwitcher)
	{
		PostWidgetSwitcher->SetActiveWidgetIndex(1);

		AsyncTask(ENamedThreads::GameThread, [this]()
			{
				UpdatePostWidget();
			});
	}
}

void UPostOverlayUI::OnWritePostButtonClicked()
{
	if (PostWidgetSwitcher)
	{
		PostWidgetSwitcher->SetActiveWidgetIndex(2);
	}
}

void UPostOverlayUI::SetMaxSlotCount(int32 Count)
{
	MaxPostSlotCount = Count;
	Init();
	RefreshUI();
}

void UPostOverlayUI::UpdatePostWidget()
{
	int64 UserSeq = GameInstance->GetNetworkManager()->GetUserSeq();
	TArray<FPostResult> PostResultData = GameInstance->GetPostalManager()->GetPostData();
	TArray<FPostResult> ReceivedPostList; 
	TArray<FPostResult> SentPostList; 
	
	for (FPostResult PostData : PostResultData)
	{
		if (PostData.SenderSeq == UserSeq)
		{
			SentPostList.Add(PostData);
		}
		if (PostData.ReceiverSeq == UserSeq)
		{
			ReceivedPostList.Add(PostData);
		}
	}
	if(ReceivedPostList.Num() > 0 && PostReceivedTabWidget)
		PostReceivedTabWidget->UpdatePostList(ReceivedPostList, false);
	if(SentPostList.Num() > 0 && PostSentTabWidget)
		PostSentTabWidget->UpdatePostList(SentPostList, true);
}

void UPostOverlayUI::SetPostResults(const TArray<FPostResult>& NewPostResult)
{
	FScopeLock Lock(&PostDataMutex);
	PostResults = NewPostResult;
}