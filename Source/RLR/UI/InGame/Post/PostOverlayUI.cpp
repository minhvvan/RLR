// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Post/PostTabWidget.h"
#include "UI/InGame/Post/PostButtonUI.h"
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
#include "Components/SizeBox.h"
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
	{
		ReceivedPostButton->OnClicked.AddUniqueDynamic(this, &UPostOverlayUI::OnReceivedPostButtonClicked);
	}
	if (SentPostButton)
	{
		SentPostButton->OnClicked.AddUniqueDynamic(this, &UPostOverlayUI::OnSentPostButtonClicked);
	}
	if (WritePostButton)
	{
		WritePostButton->OnClicked.AddUniqueDynamic(this, &UPostOverlayUI::OnWritePostButtonClicked);
	}
	if (PostReceivedTabWidget)
	{
		PostReceivedTabWidget->OnRemovePostsButtonClicked.AddUniqueDynamic(this, &UPostOverlayUI::ConfirmDeletePosts);
		PostReceivedTabWidget->OnRemoveOnePostButtonClicked.AddUniqueDynamic(this, &UPostOverlayUI::ConfirmDeletePost);
		PostReceivedTabWidget->OnPostReplyButtonClicked.AddUniqueDynamic(this, &UPostOverlayUI::OnReplyButtonClicked);
	}
	if(PostSentTabWidget)
	{
		PostSentTabWidget->OnRemovePostsButtonClicked.AddUniqueDynamic(this, &UPostOverlayUI::ConfirmDeletePosts);
		PostSentTabWidget->OnRemoveOnePostButtonClicked.AddUniqueDynamic(this, &UPostOverlayUI::ConfirmDeletePost);
	}
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
		if (PostWidgetSwitcher->GetActiveWidget() != PostReceivedTabWidget)
		{
			PostReceivedTabWidget->PostList_SizeBox->SetVisibility(ESlateVisibility::Hidden);
			if (PostReceivedTabWidget->SelectedPostButton != nullptr)
			{
				PostReceivedTabWidget->SelectedPostButton->SetButtonState(false);
				PostReceivedTabWidget->SelectedPostButton = nullptr;
			}
			PostReceivedTabWidget->SelectedPost = FPostResult();
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
		if (PostWidgetSwitcher->GetActiveWidget() != PostSentTabWidget)
		{
			PostSentTabWidget->PostList_SizeBox->SetVisibility(ESlateVisibility::Hidden);
			if (PostSentTabWidget->SelectedPostButton != nullptr)
			{
				PostSentTabWidget->SelectedPostButton->SetButtonState(false);
				PostSentTabWidget->SelectedPostButton = nullptr;
			}
			PostSentTabWidget->SelectedPost = FPostResult();
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

bool UPostOverlayUI::GetWritingPostStatus()
{
	/* 우편 작성 탭이 열려있고, 작성중인 내용이 있다면 */
	if (!PostWriteTabWidget->RecipientIdText->GetText().IsEmpty() || !PostWriteTabWidget->PostTitleText->GetText().IsEmpty())
	{
		return true;
	}
	return false;
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
/* 공통 작업 함수 */
void UPostOverlayUI::HandlePostAction(UConfirmMessageBox* MessageBox, EPostAction ActionType)
{
	switch (ActionType)
	{
	case EPostAction::ClearWriteTab:
		if (PostWriteTabWidget)
		{
			PostWriteTabWidget->OnClearPostButtonClicked();
			OnPostUIEnd.Broadcast();
		}
		break;

	case EPostAction::RemoveSelectedPosts:
		if (PostReceivedTabWidget)
		{
			PostReceivedTabWidget->OnRemoveSelectedButtonClicked();
		}
		if (PostSentTabWidget)
		{
			PostSentTabWidget->OnRemoveSelectedButtonClicked();
		}
		break;

	case EPostAction::RemoveSinglePost:
		if (PostReceivedTabWidget)
		{
			PostReceivedTabWidget->OnRemoveButtonClicked();
		}
		if (PostSentTabWidget)
		{
			PostSentTabWidget->OnRemoveButtonClicked();
		}
		break;
	}

	if (ConfirmMessageBox)
	{
		ConfirmMessageBox->SetVisibility(ESlateVisibility::Hidden);
	}
}
/* 우편 작성 중 나가기 버튼 클릭 시 뜨는 팝업에 수락 */
void UPostOverlayUI::OnClickedAcceptButton(UConfirmMessageBox* MessageBox)
{
	HandlePostAction(MessageBox, EPostAction::ClearWriteTab);
}

/* 여러 우편 삭제 수락 */
void UPostOverlayUI::OnClickedDeletePostsConfirmButton(UConfirmMessageBox* MessageBox)
{
	HandlePostAction(MessageBox, EPostAction::RemoveSelectedPosts);
}

/* 우편 한 개 삭제 수락 */
void UPostOverlayUI::OnClickedDeletePostConfirmButton(UConfirmMessageBox* MessageBox)
{
	HandlePostAction(MessageBox, EPostAction::RemoveSinglePost);
}

/* 우편 답신 기능 */
void UPostOverlayUI::OnReplyButtonClicked(FText IdText)
{
	/* writeTab으로 전환, writetab의 받는 이 닉네임을 나에게 우편 보낸 이로 채우기 */
	PostWidgetSwitcher->SetActiveWidget(PostWriteTabWidget);
	PostWriteTabWidget->RecipientIdText->SetText(IdText);
}

void UPostOverlayUI::OnClickedCancelButton(UConfirmMessageBox* MessageBox)
{
	ConfirmMessageBox->SetVisibility(ESlateVisibility::Hidden);
}

/* Confirm Message 상황에 맞게 세팅 */
void UPostOverlayUI::ShowConfirmMessage(const FText& MessageText, FName ConfirmFunctionName, FName CancelFunctionName)
{
	if (!ConfirmMessageBox) return;

	// 팝업 표시
	ConfirmMessageBox->SetVisibility(ESlateVisibility::Visible);

	// 메시지 설정
	ConfirmMessageBox->SetMessageText(MessageText);

	// 기존 바인딩 제거
	ConfirmMessageBox->OnConfirmButtonClickedDelegate.Clear();
	ConfirmMessageBox->OnCancelButtonClickedDelegate.Clear();

	// 새 바인딩 등록
	ConfirmMessageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, ConfirmFunctionName);
	ConfirmMessageBox->OnCancelButtonClickedDelegate.BindUFunction(this, CancelFunctionName);
}

/* 여러 우편 삭제 ConfirmMessage */
void UPostOverlayUI::ConfirmDeletePosts()
{
	FText Text = STRING_TO_FTEXT("정말 삭제하시겠습니까? 다시 되돌릴 수 없습니다.");
	ShowConfirmMessage(
		Text,
		FName("OnClickedDeletePostsConfirmButton"),
		FName("OnClickedCancelButton")
	);
}

/* 한 개 우편 삭제 ConfirmMessage */
void UPostOverlayUI::ConfirmDeletePost()
{
	FText Text = STRING_TO_FTEXT("정말 삭제하시겠습니까? 다시 되돌릴 수 없습니다.");
	ShowConfirmMessage(
		Text,
		FName("OnClickedDeletePostConfirmButton"),
		FName("OnClickedCancelButton")
	);
}

/* 작성 중 나가기 ConfirmMessage */
void UPostOverlayUI::ManageWritingPost()
{
	FText Text = STRING_TO_FTEXT("작성중인 우편이 있습니다. 창을 종료하면 작성 중이던 편지가 삭제됩니다.");
	ShowConfirmMessage(
		Text,
		FName("OnClickedAcceptButton"),
		FName("OnClickedCancelButton")
	);
	ChangeTabIndex = 1;
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