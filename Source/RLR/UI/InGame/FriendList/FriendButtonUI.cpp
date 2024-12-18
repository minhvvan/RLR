// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendButtonUI.h"
#include "UI/InGame/FriendList/FriendRequestTabWidget.h"
#include "UI/InGame/FriendList/FriendListUI.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameManager/GameManager.h"
#include "GameManager/FriendManager.h"
#include "GameManager/NetworkManager.h"

#include "GameManager/OtherUserManager.h"

void UFriendButtonUI::NativeConstruct()
{
    SetButtonState(false);
    if (FriendButton && IsValid(FriendButton) && !bIsFriendRequestTab)
    {
        FriendButton->OnClicked.RemoveDynamic(this, &UFriendButtonUI::OnFriendButtonClicked);
        FriendButton->OnClicked.AddDynamic(this, &UFriendButtonUI::OnFriendButtonClicked);
    }
    if (bIsFriendRequestTab && AcceptRequestButton)
    {
        AcceptRequestButton->OnClicked.AddDynamic(this, &UFriendButtonUI::OnAcceptRequestClicked);
    }
}

void UFriendButtonUI::SetFriendInfo(int NewFriendSeq, FString NewFriendName)
{
    FriendSeq = NewFriendSeq;
    FriendName = NewFriendName;
    if(FriendNameText)
        FriendNameText->SetText(FText::FromString(FriendName));
	if (PlayerLevelText)
	{
        auto Player = GameInstance->GetOtherUserManager()->GetPlayer(FriendSeq);
        if (Player)
        {
            auto Stat = Player->GetStat();
            if (Stat)
            {
                int32 playerLevel = Stat->GetLevel();
                PlayerLevelText->SetText(FText::AsNumber(playerLevel));
            }

        }
	}
    if (PlayerLocation)
    {
        /* player 위치 받아오기 */
    }
    if (CurrentConnectDate)
    {
        /* 최근 접속 일자 받아오기 */
    }
}

void UFriendButtonUI::OnFriendButtonClicked()
{
    OnFriendRequestButtonClick.Broadcast(FriendSeq, this);
}

void UFriendButtonUI::OnAcceptRequestClicked()
{
    GameInstance->GetNetworkManager()->SendAddFriend(FriendName);
    GameInstance->GetFriendManager()->DeleteFromRequestList(FriendSeq);
    if (GameInstance->GetFriendManager()->FriendListUI && GameInstance->GetFriendManager()->FriendListUI->FriendRequestTabWidget)
    {
        GameInstance->GetFriendManager()->FriendListUI->FriendRequestTabWidget->UpdateFriendRequestTab(GameInstance->GetFriendManager()->GetRequestFriendData());
    }
}

void UFriendButtonUI::SetButtonState(bool isPressed)
{
    FSlateBrush PressedBrush;
    FSlateBrush NormalBrush;
    FButtonStyle ButtonStyle = FriendButton->GetStyle();

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
        ButtonStyle.SetNormal(PressedBrush);
        ButtonStyle.SetHovered(PressedBrush);
        ButtonStyle.SetPressed(PressedBrush);
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
