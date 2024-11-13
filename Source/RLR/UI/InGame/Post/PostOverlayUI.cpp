// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Post/PostTabWidget.h"
#include "UI/InGame/Post/PostWriteTabWidget.h"
#include "UI/InGame/Post/InputTransactionCost.h"
#include "UI/InGame/Popup/ConfirmMessageBox.h"

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
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void UPostOverlayUI::NativeConstruct()
{
	Super::NativeConstruct();

	SetUITag(FGameplayTagManager::Get().UI_Post);

	GameInstance->GetPostalManager()->PostUIClass = this;
	if (ReceivedPostButton)
		ReceivedPostButton->OnClicked.AddUniqueDynamic(this, &UPostOverlayUI::OnReceivedPostButtonClicked);
	if (SentPostButton)
		SentPostButton->OnClicked.AddUniqueDynamic(this, &UPostOverlayUI::OnSentPostButtonClicked);
	if (WritePostButton)
		WritePostButton->OnClicked.AddUniqueDynamic(this, &UPostOverlayUI::OnWritePostButtonClicked);
}

void UPostOverlayUI::Init()
{
	//CreatePostSlots();

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

	//PostWriteTabWidget->PostSlotList.Empty();
	//PostWriteTabWidget->PostSlotList.Init(nullptr, MaxPostSlotCount);

	if (PostItemSlotClass == nullptr)
	{
		DEBUG_MESSAGE;
		return;
	}

	for (int32 Count = 0; Count < MaxPostSlotCount; Count++)
	{
		// PostWriteTabWidget에 슬롯 추가
		UPostItemSlot* WriteSlot = CreateWidget<UPostItemSlot>(this, PostItemSlotClass);
		/*PostWriteTabWidget->PostSlotList[Count] = WriteSlot;*/
		WriteSlot->SlotIndex = Count;
		WriteSlot->PostUI = this;
		PostWriteTabWidget->PostSlotGridPanel->AddChildToGrid(WriteSlot, 0, Count);

		if (PostReceivedTabWidget->PostSlotGridPanel->GetChildrenCount() == 0)
		{
			// PostReceivedTabWidget에 슬롯 추가
			UPostItemSlot* ReceivedSlot = CreateWidget<UPostItemSlot>(this, PostItemSlotClass);
			ReceivedSlot->SlotIndex = Count;
			ReceivedSlot->PostUI = this;
			PostReceivedTabWidget->PostSlotGridPanel->AddChildToGrid(ReceivedSlot, 0, Count);
		}

	}
}

void UPostOverlayUI::CreatePostSlotWriteTab(int32 SlotCount)
{
	TSubclassOf<UPostItemSlot> PostItemSlotClass = GameInstance->GetDataManager()->GetWidgetClass<UPostItemSlot>("WBP_PostItemSlot");
	for (int32 Count = 0; Count < SlotCount; Count++)
	{
		// PostReceivedTabWidget에 슬롯 추가
		UPostItemSlot* ReceivedSlot = CreateWidget<UPostItemSlot>(this, PostItemSlotClass);
		ReceivedSlot->SlotIndex = Count;
		ReceivedSlot->PostUI = this;
		PostReceivedTabWidget->PostSlotGridPanel->AddChildToGrid(ReceivedSlot, 0, Count);
	}
}

void UPostOverlayUI::CreatePostSlotSentTab(int32 SlotCount)
{
	TSubclassOf<UPostItemSlot> PostItemSlotClass = GameInstance->GetDataManager()->GetWidgetClass<UPostItemSlot>("WBP_PostItemSlot");
	for (int32 Count = 0; Count < SlotCount; Count++)
	{
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
		if (PostWidgetSwitcher->GetActiveWidgetIndex() == 2)
		{
			/* 우편 작성 탭이 열려있고, 작성중인 내용이 있다면 */
			if (!PostWriteTabWidget->RecipientIdText->GetText().IsEmpty() || !PostWriteTabWidget->PostTitleText->GetText().IsEmpty())
			{
				/* "작성중이던 우편이 있습니다" 팝업 띄우기 */
				ConfirmMessageBox->SetVisibility(ESlateVisibility::Visible);
				FText MessageText = STRING_TO_FTEXT("작성중인 우편이 있습니다. 창을 종료하면 작성 중이던 편지가 삭제됩니다.");
				ConfirmMessageBox->SetMessageText(MessageText);

				//클릭, 취소 버튼 콜백 함수 등록
				ConfirmMessageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, FName("OnClickedAcceptButton"));
				ConfirmMessageBox->OnCancelButtonClickedDelegate.BindUFunction(this, FName("OnClickedCancelButton"));

				ChangeTabIndex = 0;
				return;
			}
		}
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
		if (PostWidgetSwitcher->GetActiveWidgetIndex() == 2)
		{
			/* 우편 작성 탭이 열려있고, 작성중인 내용이 있다면 */
			if (!PostWriteTabWidget->RecipientIdText->GetText().IsEmpty() || !PostWriteTabWidget->PostTitleText->GetText().IsEmpty())
			{
				/* "작성중이던 우편이 있습니다" 팝업 띄우기 */
				ConfirmMessageBox->SetVisibility(ESlateVisibility::Visible);
				FText MessageText = STRING_TO_FTEXT("작성중인 우편이 있습니다. 창을 종료하면 작성 중이던 편지가 삭제됩니다.");
				ConfirmMessageBox->SetMessageText(MessageText);

				//클릭, 취소 버튼 콜백 함수 등록
				ConfirmMessageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, FName("OnClickedAcceptButton"));
				ConfirmMessageBox->OnCancelButtonClickedDelegate.BindUFunction(this, FName("OnClickedCancelButton"));

				ChangeTabIndex = 1;
				return;
			}
		}

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

void UPostOverlayUI::OnClickedAcceptButton(UConfirmMessageBox* MessageBox)
{
	if (PostWriteTabWidget)
	{
		/* 작성하던 내용 모두 초기화 */
		PostWriteTabWidget->OnClearPostButtonClicked();
		ConfirmMessageBox->SetVisibility(ESlateVisibility::Hidden);
		/* 열려고 했던 창 열기 */
		if (PostWidgetSwitcher)
		{
			PostWidgetSwitcher->SetActiveWidgetIndex(ChangeTabIndex);
		}
	}
}

void UPostOverlayUI::OnClickedCancelButton(UConfirmMessageBox* MessageBox)
{
	ConfirmMessageBox->SetVisibility(ESlateVisibility::Hidden);
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