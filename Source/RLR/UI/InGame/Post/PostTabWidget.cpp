// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostTabWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/EditableText.h"
#include "Components/MultiLineEditableText.h"
#include "Components/GridPanel.h"
#include "Structs/UtilStructs.h"
#include "GameManager/GameManager.h"
#include "GameManager/PostalManager.h"
#include "UI/InGame/Post/PostButtonUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/PostalManager.h"

void UPostTabWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UPostTabWidget::UpdatePostList(const TArray<FPostResult>& Posts, bool bIsSent)
{
    bIsSentTab = bIsSent;
    ClearPostList();

    for (const FPostResult& Post : Posts)
    {
        AddPostButton(Post, bIsSentTab);
    }
}

void UPostTabWidget::RemovePost(FPostResult Post)
{
    AsyncTask(ENamedThreads::GameThread, [this, Post]()
        {
            for (auto* ChildWidget : PostScrollBox->GetAllChildren())
            {
                if (UPostButtonUI* PostButton = Cast<UPostButtonUI>(ChildWidget))
                {
                    if (PostButton->GetPostTitle() == SelectedPost.Title)
                    {
                        PostScrollBox->RemoveChild(PostButton);
                        PostButton->SetButtonState(false);
                        break;
                    }
                }
            }
            PostButtons.Remove(SelectedPost.Title);
            SelectedPost = FPostResult();
            UpdatePostDetails(SelectedPost);
        });
}

void UPostTabWidget::OnRemoveButtonClicked()
{
    // 구현 필요
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
}

void UPostTabWidget::OnPostButtonClicked(const FPostResult& ClickedPost, UPostButtonUI* PostButtonUI)
{
    PostButtonUI->SetButtonState(true);
    if (!SelectedPost.Title.IsEmpty())
    {
        UPostButtonUI* PrevButton = *PostButtons.Find(SelectedPost.Title);
        if (PrevButton)
        {
            PrevButton->SetButtonState(false);
        }
    }
    UpdatePostDetails(ClickedPost);
}