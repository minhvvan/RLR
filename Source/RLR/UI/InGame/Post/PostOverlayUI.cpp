// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Post/PostTabWidget.h"
#include "UI/InGame/Post/PostButtonUI.h"
#include "UI/InGame/Post/PostDetailUI.h"
#include "UI/InGame/Post/PostWriteTabWidget.h"
#include "UI/InGame/Post/InputTransactionCost.h"
#include "UI/InGame/Popup/ConfirmMessageBox.h"

#include "GameManager/PostalManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/LiteralManager.h"
#include "GameManager/UIManager.h"

#include "Structs/UtilStructs.h"
#include "Components/GridPanel.h"
#include "Components/CanvasPanel.h"
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

	DeletePostsConfirmText = FSTRING_TO_FTEXT(RLRLITERAL.PostUI_RemovePrompt);
	WritingPostWarningText = FSTRING_TO_FTEXT(RLRLITERAL.PostUI_ExitPrompt);

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
		PostReceivedTabWidget->PostOverlayUI = this;
	}
	if(PostSentTabWidget)
	{
		PostSentTabWidget->OnRemovePostsButtonClicked.AddUniqueDynamic(this, &UPostOverlayUI::ConfirmDeletePosts);
		PostSentTabWidget->PostOverlayUI = this;
	}
	if (PostDetailUI)
	{
		PostDetailUI->OnRemoveOnePostButtonClicked.AddUniqueDynamic(this, &UPostOverlayUI::ConfirmDeletePosts);
		PostDetailUI->OnPostReplyButtonClicked.AddUniqueDynamic(this, &UPostOverlayUI::OnReplyButtonClicked);
	}
}

void UPostOverlayUI::Init()
{
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

bool UPostOverlayUI::CanSendItem()
{
	if (UPostWriteTabWidget* WriteTab = Cast<UPostWriteTabWidget>(PostWidgetSwitcher->GetActiveWidget()))
	{
		return true;
	}
	return false;
}

UPanelSlot* UPostOverlayUI::AddChild(UUserWidget* Child)
{
	return Canvas->AddChild(Child);
}

void UPostOverlayUI::OnReceivedPostButtonClicked()
{
	if (PostWidgetSwitcher)
	{
		if (PostWidgetSwitcher->GetActiveWidget() != PostReceivedTabWidget)
		{
			FText TabNameText = FSTRING_TO_FTEXT(RLRLITERAL.PostUI_ReceivedPost);
			PostDetailUI->SetVisibility(ESlateVisibility::Hidden);
			PostDetailUI->SetTabNameText(TabNameText);
			PostDetailUI->ReplyButton->SetVisibility(ESlateVisibility::Visible);
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
			FText TabNameText = FSTRING_TO_FTEXT(RLRLITERAL.PostUI_SentPost);
			PostDetailUI->SetVisibility(ESlateVisibility::Hidden);
			PostDetailUI->SetTabNameText(TabNameText);
			PostDetailUI->ReplyButton->SetVisibility(ESlateVisibility::Hidden);
			if (PostSentTabWidget->SelectedPostButton != nullptr)
			{
				PostSentTabWidget->SelectedPostButton->SetButtonState(false);
				PostSentTabWidget->SelectedPostButton = nullptr;
			}
			PostSentTabWidget->SelectedPost = FPostResult();
		}
		PostWidgetSwitcher->SetActiveWidgetIndex(1); 
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
		PostDetailUI->SetVisibility(ESlateVisibility::Hidden);
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

/* 우편 작성 중 나가기 버튼 클릭 시 뜨는 팝업에 수락 */
void UPostOverlayUI::OnClickedAcceptButton(UConfirmMessageBox* MessageBox)
{
	if (PostWriteTabWidget)
	{
		PostWriteTabWidget->OnClearPostButtonClicked();
		OnPostUIEnd.Broadcast();
	}
	ConfirmMessageBox->SetVisibility(ESlateVisibility::Hidden);
}

/* 여러 우편 삭제 수락 */
void UPostOverlayUI::OnClickedDeletePostsConfirmButton(UConfirmMessageBox* MessageBox)
{
	if (PostReceivedTabWidget)
	{
		PostReceivedTabWidget->OnRemoveSelectedButtonClicked();
	}
	if (PostSentTabWidget)
	{
		PostSentTabWidget->OnRemoveSelectedButtonClicked();
	}
	ConfirmMessageBox->SetVisibility(ESlateVisibility::Hidden);
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

	ConfirmMessageBox->SetVisibility(ESlateVisibility::Visible);

	ConfirmMessageBox->SetMessageText(MessageText);

	ConfirmMessageBox->OnConfirmButtonClickedDelegate.Clear();
	ConfirmMessageBox->OnCancelButtonClickedDelegate.Clear();

	ConfirmMessageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, ConfirmFunctionName);
	ConfirmMessageBox->OnCancelButtonClickedDelegate.BindUFunction(this, CancelFunctionName);
}

/* 여러 우편 삭제 ConfirmMessage */
void UPostOverlayUI::ConfirmDeletePosts()
{
	ShowConfirmMessage(
		DeletePostsConfirmText,
		RLRLITERAL.PostUI_OnClickedDeletePostsConfirmButton,
		RLRLITERAL.PostUI_OnClickedCancelButton
	);
}

/* 작성 중 나가기 ConfirmMessage */
void UPostOverlayUI::ManageWritingPost()
{
	ShowConfirmMessage(
		WritingPostWarningText,
		RLRLITERAL.PostUI_OnClickedAcceptButtonWhileWriting,
		RLRLITERAL.PostUI_OnClickedCancelButton
	);
	ChangeTabIndex = 1;
}

void UPostOverlayUI::UpdatePostWidget()
{
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