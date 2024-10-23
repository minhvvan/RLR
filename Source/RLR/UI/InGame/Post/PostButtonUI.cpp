// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostButtonUI.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameManager.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void UPostButtonUI::NativeConstruct()
{
    SetButtonState(false);
    if (PostButton)
    {
        PostButton->OnClicked.AddDynamic(this, &UPostButtonUI::OnPostButtonClicked);
    }
}

void UPostButtonUI::NativePreConstruct()
{
    SetDesiredSizeInViewport(FVector2D(200, 50));
}

void UPostButtonUI::OnPostButtonClicked()
{
    SetButtonState(true);
    OnPostButtonClick.Broadcast(PostInfo, this);
    GameInstance->GetNetworkManager()->SendPostReadRequest(PostInfo);
}

void UPostButtonUI::SetPostInfo(const FPostResult& InPost, bool bIsSentPost)
{
    PostInfo = InPost;
    if (PostTitleText)
    {
        PostTitleText->SetText(FText::FromString(PostInfo.Title));
    }
    if (PostNameText)
    {
        FString Name;
        if (bIsSentPost)
        {
            Name = FString::FromInt(PostInfo.ReceiverSeq);
        }
        else
        {
            Name = FString::FromInt(PostInfo.SenderSeq);
        }
        PostNameText->SetText(FText::FromString(Name));
    }
}

void UPostButtonUI::SetReceivedPostInfo(const FPostResult& InPost)
{
    PostInfo = InPost;
    if (PostTitleText)
    {
        PostTitleText->SetText(FText::FromString(PostInfo.Title));
    }
    if (PostNameText)
    {
        /* 일단은 Seq로 설정*/
        FString SenderName = FString::FromInt(PostInfo.SenderSeq);
        PostNameText->SetText(FText::FromString(SenderName));
    }
}

void UPostButtonUI::SetSentPostInfo(const FPostResult& InPost)
{
    PostInfo = InPost;
    if (PostTitleText)
    {
        PostTitleText->SetText(FText::FromString(PostInfo.Title));
    }
    if (PostNameText)
    {
        /* 일단은 Seq로 설정*/
        FString ReceiverName = FString::FromInt(PostInfo.ReceiverSeq);
        PostNameText->SetText(FText::FromString(ReceiverName));
    }
}

void UPostButtonUI::SetButtonState(bool isPressed)
{
    FSlateBrush PressedBrush;
    FSlateBrush NormalBrush;

    FButtonStyle ButtonStyle = PostButton->WidgetStyle;

    if (isPressed)
    {
        PressedBrush.TintColor = FSlateColor(FLinearColor(0.f, 0.f, 0.f));
        
        ButtonStyle.SetNormal(PressedBrush);
        ButtonStyle.SetHovered(PressedBrush);
        ButtonStyle.SetPressed(PressedBrush);
    }
    else
    {
        NormalBrush.TintColor = FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f));

        ButtonStyle.SetNormal(NormalBrush);
        ButtonStyle.SetHovered(NormalBrush);
        ButtonStyle.SetPressed(NormalBrush);
    }
}

FString UPostButtonUI::GetPostTitle()
{
    return PostInfo.Title;
}