// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Post/PostTabWidget.h"
#include "UI/InGame/Post/PostWriteTabWidget.h"
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

	GameInstance->GetPostalManager()->PostUIClass = this;
	if (ReceivedPostButton)
		ReceivedPostButton->OnClicked.AddDynamic(this, &UPostOverlayUI::OnReceivedPostButtonClicked);
	if (SentPostButton)
		SentPostButton->OnClicked.AddDynamic(this, &UPostOverlayUI::OnSentPostButtonClicked);
	if (WritePostButton)
		WritePostButton->OnClicked.AddDynamic(this, &UPostOverlayUI::OnWritePostButtonClicked);
}

void UPostOverlayUI::Init()
{
	CreatePostSlots();

	PostWidgetSwitcher->SetActiveWidgetIndex(0);
	GameInstance->GetNetworkManager()->SendPostGetRequest();
	OnPostGetRequestComplete();
}

void UPostOverlayUI::RefreshUI()
{
	// 서버나 캐시에서 새 우편 데이터 가져오기
	TArray<FPostResult> NewSentPostData = GameInstance->GetPostalManager()->GetSentPostData();
	SetSentPostData(NewSentPostData);

	TArray<FPostResult> NewRecvPostData = GameInstance->GetPostalManager()->GetReceivedPostData();
	SetRecvPostData(NewRecvPostData);

	UpdatePostWidget();
}

void UPostOverlayUI::CreatePostSlots()
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
		// PostWriteTabWidget에 슬롯 추가
		UPostItemSlot* WriteSlot = CreateWidget<UPostItemSlot>(this, PostItemSlotClass);
		PostWriteTabWidget->PostSlotList[Count] = WriteSlot;
		WriteSlot->SlotIndex = Count;
		WriteSlot->PostUI = this;
		PostWriteTabWidget->PostSlotGridPanel->AddChildToGrid(WriteSlot, 0, Count);

		// PostReceivedTabWidget에 슬롯 추가
		UPostItemSlot* ReceivedSlot = CreateWidget<UPostItemSlot>(this, PostItemSlotClass);
		ReceivedSlot->SlotIndex = Count;
		ReceivedSlot->PostUI = this;
		PostReceivedTabWidget->PostSlotGridPanel->AddChildToGrid(ReceivedSlot, 0, Count);

		// PostSentTabWidget에 슬롯 추가
		UPostItemSlot* SentSlot = CreateWidget<UPostItemSlot>(this, PostItemSlotClass);
		SentSlot->SlotIndex = Count;
		SentSlot->PostUI = this;
		PostSentTabWidget->PostSlotGridPanel->AddChildToGrid(SentSlot, 0, Count);
	}
}

void UPostOverlayUI::OnReceivedPostButtonClicked()
{
	if (PostWidgetSwitcher)
	{
		PostWidgetSwitcher->SetActiveWidgetIndex(0);
		GameInstance->GetNetworkManager()->SendPostGetRequest();
		OnPostGetRequestComplete();
	}
}

void UPostOverlayUI::OnPostGetRequestComplete()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			UpdatePostWidget();
		});
}

void UPostOverlayUI::OnSentPostButtonClicked()
{
	if (PostWidgetSwitcher)
	{
		PostWidgetSwitcher->SetActiveWidgetIndex(1); // 발신함 위젯으로 전환
		GameInstance->GetNetworkManager()->SendPostGetRequest();
		OnPostSentRequestComplete();
	}
}

void UPostOverlayUI::OnPostSentRequestComplete()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			UpdatePostWidget();
		});
}

void UPostOverlayUI::OnWritePostButtonClicked()
{
	if (PostWidgetSwitcher)
	{
		PostWidgetSwitcher->SetActiveWidgetIndex(2);
		GameInstance->GetNetworkManager()->SendPostGetRequest();
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
	//int64 UserSeq = GameInstance->GetNetworkManager()->GetUserSeq();
	TArray<FPostResult> PostSentData = GameInstance->GetPostalManager()->GetSentPostData();
	TArray<FPostResult> PostRecvData = GameInstance->GetPostalManager()->GetReceivedPostData();
	TArray<FPostResult> ReceivedPostList; 
	TArray<FPostResult> SentPostList; 
	
	for (FPostResult PostData : PostSentData)
	{
		SentPostList.Add(PostData);
	}
	for (FPostResult PostData : PostRecvData)
	{
		ReceivedPostList.Add(PostData);
	}

	if(ReceivedPostList.Num() > 0 && PostReceivedTabWidget)
		PostReceivedTabWidget->UpdatePostList(ReceivedPostList, false);
	if(SentPostList.Num() > 0 && PostSentTabWidget)
		PostSentTabWidget->UpdatePostList(SentPostList, true);
}

void UPostOverlayUI::SetSentPostData(const TArray<FPostResult>& NewPostResult)
{
	FScopeLock Lock(&PostDataMutex);
	SentPostData = NewPostResult;
}

void UPostOverlayUI::SetRecvPostData(const TArray<FPostResult>& NewPostResult)
{
	FScopeLock Lock(&PostDataMutex);
	RecvPostData = NewPostResult;
}