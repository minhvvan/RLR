// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostAlertUI.h"
#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/PostTabWidget.h"
#include "Components/GridPanel.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/MultiLineEditableText.h"
#include "GameManager/PostalManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/NetworkManager.h"
#include "Blueprint/WidgetLayoutLibrary.h"


void UPostAlertUI::NativeConstruct()
{
	Super::NativeConstruct();

    if (CloseButton)
    {
        CloseButton->OnClicked.AddDynamic(this, &UPostAlertUI::OnCloseButtonClicked);
    }
    if (RemovePostButton)
    {
        RemovePostButton->OnClicked.AddDynamic(this, &UPostAlertUI::OnRemovePostButtonClicked);
    }
    if (AcceptAllButton)
    {
        AcceptAllButton->OnClicked.AddDynamic(this, &UPostAlertUI::OnAcceptButtonClicked);
    }
}

void UPostAlertUI::UpdatePost(const FPostResult& Post)
{
    PostData = Post;

    IdText->SetIsReadOnly(true);
    PostTitleText->SetIsReadOnly(true);
    PostContentText->SetIsReadOnly(true);
    TotalMoney->SetIsReadOnly(true);

    IdText->SetText(FText::AsNumber(Post.SenderSeq));
    PostTitleText->SetText(FText::FromString(Post.Title));
    PostContentText->SetText(FText::FromString(Post.Content));
    TotalMoney->SetText(FText::AsNumber(Post.TotalMoney));
}

void UPostAlertUI::UpdatePostItemSlot(const FPostResult& Post)
{
    for (int i = 0; i < 7; i++)
    {
        UPostItemSlot* itemSlot = Cast<UPostItemSlot>(PostSlotGridPanel->GetChildAt(i));
        if (!Post.ItemId.IsEmpty() && Post.ItemId[i] != 0)
        {
            if (IsValid(itemSlot))
            {
                itemSlot->SetSlot(Post.ItemId[i]);
            }
        }
    }
}

void UPostAlertUI::OnCloseButtonClicked()
{
    RemoveFromParent();
}

void UPostAlertUI::OnAcceptButtonClicked()
{
    /* 
        인벤토리에 아이템 추가, 재화 추가
        GameInstance->GetNetWorkManager()->SendPostReceivedRequest(Post);
    */
}

void UPostAlertUI::OnRemovePostButtonClicked()
{
    if (GameInstance->GetPostalManager()->PostUIClass)
    {
        GameInstance->GetPostalManager()->AddToPostDeletionList(PostData, false);
        /* 현재 postId가 1로 통일이라 우편 순서대로 삭제되는 중 나중에 고쳐질 것임*/
        GameInstance->GetNetworkManager()->SendPostRemoveRequest(PostData);
    }
    RemoveFromParent();
}