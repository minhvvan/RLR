// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostTabWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/MultiLineEditableText.h"
#include "Components/GridPanel.h"
#include "Structs/UtilStructs.h"
#include "GameManager/GameManager.h"
#include "GameManager/PostalManager.h"
#include "GameManager/NetworkManager.h"
#include "UI/InGame/Post/PostButtonUI.h"
#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/PostItemSlot.h"



void UPostTabWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (RemovePostButton)
    {
        RemovePostButton->OnClicked.AddDynamic(this, &UPostTabWidget::OnRemoveButtonClicked);
    }
}

void UPostTabWidget::UpdatePostList(const TArray<FPostResult>& Posts, bool bIsSent)
{
    bIsSentTab = bIsSent;
    ClearPostList();

    for (const FPostResult& Post : Posts)
    {
        AddPostButton(Post, bIsSentTab);
        /* alert에서 삭제하기로 예약해둔 우편들 삭제 */

        for (int i = 0; i < 7; i++)
        {
            UPostItemSlot* itemSlot = Cast<UPostItemSlot>(PostSlotGridPanel->GetChildAt(i));
            if (!Post.ItemId.IsEmpty() && Post.ItemId[i] != 0)
            {
                itemSlot->SetSlot(Post.ItemId[i]);
            }
        }
    }

    if (!bIsSentTab)
    {
        TArray<FPostResult> DeletionList = GameInstance->GetPostalManager()->GetAndClearPostDeletionList(false);
        for (const FPostResult& PostData : DeletionList)
        {
            RemovePost(PostData);
        }
    }
}

void UPostTabWidget::RemovePost(FPostResult Post)
{
    AsyncTask(ENamedThreads::GameThread, [this, Post]()
        {
            if (PostButtons.Contains(Post.Title))
            {
                UPostButtonUI* PostButton = PostButtons[Post.Title];
                PostScrollBox->RemoveChild(PostButton);
                PostButton->SetButtonState(false);
            }

            /* TODO : 서버에 삭제된 우편을 제외한 post목록을 전달하여 목록 새로고침하기 */
            PostButtons.Remove(SelectedPost.Title);
            SelectedPost = FPostResult();
            UpdatePostDetails(SelectedPost);
            GameInstance->GetNetworkManager()->SendPostRemoveRequest(Post);
        });
}

void UPostTabWidget::OnAcceptButtonClicked()
{
    /*
		인벤토리에 아이템 추가, 재화 추가
		GameInstance->GetNetWorkManager()->SendPostReceivedRequest(Post);
    */
}

void UPostTabWidget::OnRemoveButtonClicked()
{
    RemovePost(SelectedPost);
}

void UPostTabWidget::ClearPostList()
{
    if (!IsInGameThread())
    {
        AsyncTask(ENamedThreads::GameThread, [this]()
            {
                ClearPostList();
            });
        return;
    }

    if (PostScrollBox)
    {
        TArray<UWidget*> ChildrenToRemove = PostScrollBox->GetAllChildren();
        for (UWidget* Child : ChildrenToRemove)
        {
            if (Child)
            {
                PostScrollBox->RemoveChild(Child);
            }
        }
    }

    PostButtons.Empty();
}

void UPostTabWidget::AddPostButton(const FPostResult& Post, bool bIsSent)
{
    AsyncTask(ENamedThreads::GameThread, [this, Post, bIsSent]()
        {
            if (PostScrollBox && PostButtonUIClass)
            {
                UPostButtonUI* PostButton = CreateWidget<UPostButtonUI>(this, PostButtonUIClass);
                if (PostButton)
                {
                    PostButton->SetPostInfo(Post, bIsSent);
                    PostButton->OnPostButtonClick.AddUObject(this, &UPostTabWidget::OnPostButtonClicked);
                    PostScrollBox->AddChild(PostButton);
                    PostButtons.Add(Post.Title, PostButton);
                }
            }
        });
}

void UPostTabWidget::UpdatePostDetails(const FPostResult& Post)
{
    SelectedPost = Post;
    GameInstance->GetPostalManager()->PostUIClass->CreatePostSlots();
    
    if (IdText)
    {
        IdText->SetText(FText::FromString(FString::FromInt(bIsSentTab ? Post.ReceiverSeq : Post.SenderSeq)));
    }
    if (PostTitleText)
    {
        PostTitleText->SetText(FText::FromString(Post.Title));
    }
    if (PostContentText)
    {
        PostContentText->SetText(FText::FromString(Post.Content));
    }
    if (PostSlotGridPanel)
    {
        // PostalManager->GetPostData()의 ItemId가 있다면 GridPanel에 표시
    }
    if (TotalMoney)
    {
        TotalMoney->SetText(FText::AsNumber(Post.TotalMoney));
    }
    if (ReadStatus)
    {
        ReadStatus->SetText(FText::FromString("Read"));
    }
}

void UPostTabWidget::OnPostButtonClicked(const FPostResult& ClickedPost, UPostButtonUI* PostButtonUI)
{
    /* TODO : 현재 서버에서 postid를 1로 고정하고 있음, 나중에는 postid가 고유 값을 가질 것이기 때문에 이렇게 함 */
    // if(ClickedPost.PostId == SelectedPost.PostId) return;

    /* 이건 postid가 고유 값을 갖기 전까지 사용할 임시코드임 */
    if(SelectedPost.Title == ClickedPost.Title && SelectedPost.Content == ClickedPost.Content) return;
    PostButtonUI->SetButtonState(true);
    if (!SelectedPost.Title.IsEmpty() && PostButtons.Contains(SelectedPost.Title))
    {
        UPostButtonUI* PrevButton = *PostButtons.Find(SelectedPost.Title);
        if (PrevButton)
        {
            PrevButton->SetButtonState(false);
        }
    }
    UpdatePostDetails(ClickedPost);
}