// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendButtonUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


void UFriendButtonUI::NativeConstruct()
{
    SetButtonState(false);
    if (FriendButton && IsValid(FriendButton))
    {
        FriendButton->OnClicked.RemoveDynamic(this, &UFriendButtonUI::OnFriendButtonClicked);
        FriendButton->OnClicked.AddDynamic(this, &UFriendButtonUI::OnFriendButtonClicked);
    }
}

void UFriendButtonUI::SetFriendInfo(int NewFriendSeq, FString NewFriendName)
{
    FriendSeq = NewFriendSeq;
    FriendName = NewFriendName;
    if(FriendNameText)
        FriendNameText->SetText(FText::FromString(FriendName));
}

void UFriendButtonUI::OnFriendButtonClicked()
{
    OnFriendRequestButtonClick.Broadcast(FriendSeq, this);
}

void UFriendButtonUI::SetButtonState(bool isPressed)
{
    FSlateBrush PressedBrush;
    FSlateBrush NormalBrush;
    if (isPressed)
    {
        PressedBrush.TintColor = FSlateColor(FLinearColor(0.f, 0.f, 0.f));
        FriendButton->SetStyle(FriendButton->WidgetStyle);
        FriendButton->WidgetStyle.Normal = PressedBrush;
        FriendButton->WidgetStyle.Hovered = PressedBrush;
        FriendButton->WidgetStyle.Pressed = PressedBrush;
    }
    else
    {
        NormalBrush.TintColor = FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f));
        FriendButton->SetStyle(FriendButton->WidgetStyle);
        FriendButton->WidgetStyle.Normal = NormalBrush;
        FriendButton->WidgetStyle.Hovered = NormalBrush;
        FriendButton->WidgetStyle.Pressed = NormalBrush;
    }
}

FReply UFriendButtonUI::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
    // 우클릭 감지
    if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
    {
        // 우클릭 시 메뉴 표시
        if (OnFriendRightClicked.IsBound())
        {
            FVector2D AbsolutePosition = GetCachedGeometry().LocalToAbsolute(FVector2D::ZeroVector);
            OnFriendRightClicked.Execute(AbsolutePosition, this);
        }
        return FReply::Handled();
    }

    return Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);
}

FString UFriendButtonUI::GetFriendName()
{
	return FriendName;
}
