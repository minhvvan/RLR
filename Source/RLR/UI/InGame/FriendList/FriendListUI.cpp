// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendListUI.h"
#include "UI/InGame/FriendList/FriendTabWidget.h"
#include "UI/InGame/FriendList/FriendRequestTabWidget.h"
#include "UI/InGame/FriendList/FriendRequestMessageBox.h"
#include "UI/InGame/FriendList/FriendButtonMenu.h"
#include "UI/InGame/FriendList/GroupButtonMenu.h"
#include "UI/InGame/FriendList/FriendInformation.h"
#include "UI/InGame/FriendList/FriendButtonUI.h"
#include "UI/InGame/FriendList/GroupCreationUI.h"
#include "UI/InGame/FriendList/GroupButtonUI.h"
#include "UI/InGame/FriendList/Popup/MoveGroupMessageBox.h"
#include "UI/InGame/FriendList/Popup/AddFriendMessageBox.h"
#include "UI/InGame/FriendList/Popup/RenameGroupMessageBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/LiteralManager.h"
#include "GameManager/FriendManager.h"
#include "GameManager/GameplayTagManager.h"
#include "Structs/UtilStructs.h"


void UFriendListUI::NativeConstruct()
{
    Super::NativeConstruct();

    SetUITag(FGameplayTagManager::Get().UI_FriendList);

    bOpenRequestUI = false;
    bOpenFriendMenuUI = false;
    bOpenFriendInfoUI = false;

    FriendTabWidget->FriendListUI = this;

    if (FriendTabButton)
    {
        FriendTabButton->OnClicked.AddUniqueDynamic(this, &UFriendListUI::OnFriendTabButtonClicked);
    }
    if (FriendRequestTabButton)
    {
        FriendRequestTabButton->OnClicked.AddUniqueDynamic(this, &UFriendListUI::OnFriendRequestTabButtonClicked);
    }

    // 타이머 제거 
    GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void UFriendListUI::Init()
{
}

void UFriendListUI::RefreshUI()
{
    // UI 새로고침 로직
    GameInstance->GetFriendManager()->InitializeFriendManager();
    if (AddFriendMessageBox)
    {
        AddFriendMessageBox->OnCloseRequestUISignature.RemoveAll(this);
        // FriendRequestUI가 닫힐 때 호출될 델리게이트에 바인딩
        AddFriendMessageBox->OnCloseRequestUISignature.AddUniqueDynamic(this, &UFriendListUI::OpenFriendRequestUI);
    }
    if (RenameGroupMessageBox)
    {
        RenameGroupMessageBox->OnCloseRenameGroupSignature.AddUniqueDynamic(this, &UFriendListUI::OpenGroupRenameUI);
    }
    if (FriendTabWidget)
    {
        GameInstance->GetNetworkManager()->SendInfoFriend();
    }
	if (GroupCreationUI)
	{
        GroupCreationUI->OnGroupCreationOpen.RemoveAll(this);
		GroupCreationUI->OnGroupCreationOpen.AddDynamic(this, &UFriendListUI::OpenCreateGroupUI);
	}
    /* 열려있던 UI 닫기 */
    if (FriendMenuUI)
    {
        OpenFriendMenuUI(true);
    }
    if (GroupMenuUI)
    {
        bOpenGroupMenuUI = true;
        OpenGroupMenuUI();
    }
}

void UFriendListUI::OnFriendRightMouseClicked(FVector2D ButtonAbsolutePosition, UFriendButtonUI* FriendButtonUI)
{
    SelectedFriend = FriendButtonUI->GetFriendSeq();
    SelectedFriendName = FriendButtonUI->GetFriendName();
    FriendRelativePosition = GetCachedGeometry().AbsoluteToLocal(
        FriendButtonUI->GetCachedGeometry().LocalToAbsolute(FVector2D::Zero())
    );
    if (bOpenFriendMenuUI)
    {
        OpenFriendMenuUI(true);
    }
    else
    {
        OpenFriendMenuUI(false);
    }
}

void UFriendListUI::OnGroupRightMouseClicked(FVector2D ButtonAbsolutePosition, UGroupButtonUI* GroupButtonUI)
{
    SelectedGroup = GroupButtonUI->GetGroupSeq();
    SelectedGroupName = GroupButtonUI->GetGroupName();
    GroupRelativePosition = GetCachedGeometry().AbsoluteToLocal(
        GroupButtonUI->GetCachedGeometry().LocalToAbsolute(FVector2D::Zero())
    );
    
    OpenGroupMenuUI();
}

void UFriendListUI::SetFriendData(TArray<FFriendGroupResult> NewFriendData)
{
    FriendData = NewFriendData;
    if (FriendTabWidget)
    {
        FriendTabWidget->UpdateFriendTab(GameInstance->GetFriendManager()->GetFriendData());
    }
}

void UFriendListUI::SetFriendRequestData(TMap<int32, FString> NewFriendRequestData)
{
    FriendRequestData = NewFriendRequestData;
    if (FriendRequestTabWidget)
    {
        FriendRequestTabWidget->UpdateFriendRequestTab(GameInstance->GetFriendManager()->GetRequestFriendData());
    }
}

TArray<FFriendGroupResult>& UFriendListUI::GetFriendData()
{
    return FriendData;
}

void UFriendListUI::OnFriendTabButtonClicked()
{
    if (FriendWidgetSwitcher)
    {
        FriendWidgetSwitcher->SetActiveWidgetIndex(0);
        if (FriendTabWidget)
        {
            FriendTabWidget->UpdateFriendTab(GameInstance->GetFriendManager()->GetFriendData());
        }
    }
}

void UFriendListUI::OnFriendRequestTabButtonClicked()
{
    if (FriendWidgetSwitcher)
    {
        FriendWidgetSwitcher->SetActiveWidgetIndex(1);
        if (FriendRequestTabWidget)
        {
            FriendRequestTabWidget->UpdateFriendRequestTab(GameInstance->GetFriendManager()->GetRequestFriendData());
        }
    }
}

void UFriendListUI::OpenFriendRequestUI(bool bOpen)
{
    bOpenRequestUI = bOpen;
    if (bOpenRequestUI)
    {
        bOpenRequestUI = false;
        AddFriendMessageBox->SetVisibility(ESlateVisibility::Hidden);
    }
    else
    {
        bOpenRequestUI = true;
        if (AddFriendMessageBox)
        {
            AddFriendMessageBox->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void UFriendListUI::OpenGroupRenameUI(bool bOpen)
{
    bOpenGroupRenameUI = bOpen;
    if (bOpenGroupRenameUI)
    {
        bOpenGroupRenameUI = false;
        RenameGroupMessageBox->SetVisibility(ESlateVisibility::Hidden);
    }
    else
    {
        bOpenGroupRenameUI = true;
        if (RenameGroupMessageBox)
        {
            RenameGroupMessageBox->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void UFriendListUI::OpenFriendMenuUI(bool bOpen)
{
    bOpenFriendMenuUI = bOpen;
    if (bOpenFriendMenuUI)
    {
        bOpenFriendMenuUI = false;
        FriendMenuUI->SetVisibility(ESlateVisibility::Hidden);
    }
    else
    {
        bOpenFriendMenuUI = true;
        if (FriendMenuUI)
        {
            FWidgetTransform  position = FriendMenuUI->GetRenderTransform();
            position.Translation.X = -3.f;
            position.Translation.Y = FriendRelativePosition.Y + 13.f;
            FriendMenuUI->SetRenderTransform(position);
            FriendMenuUI->SetVisibility(ESlateVisibility::Visible);
            FriendMenuUI->SetPlayerNameText(SelectedFriendName);
            FriendMenuUI->SetFriendInfo(SelectedFriend, SelectedFriendName);
            FriendMenuUI->OnMoveGroupClicked.AddUniqueDynamic(this, &UFriendListUI::MoveGroup);
        }
    }
}

void UFriendListUI::OpenCreateGroupUI(bool bOpen)
{
    bOpenGroupCreationUI = bOpen;

    if (bOpenGroupCreationUI)
    {
        GroupCreationUI->SetVisibilityStatus(false);
        bOpenGroupCreationUI = false;
        GroupCreationUI->SetVisibility(ESlateVisibility::Hidden);
    }
    else
    {
        GroupCreationUI->SetVisibilityStatus(true);
        bOpenGroupCreationUI = true;
        if (GroupCreationUI)
        {
            GroupCreationUI->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void UFriendListUI::OpenGroupMenuUI()
{
    if (bOpenGroupMenuUI)
    {
        bOpenGroupMenuUI = false;
        GroupCreationUI->CloseUI();
        GroupMenuUI->SetVisibility(ESlateVisibility::Hidden);
        GroupMenuUI->GroupRemovedSignature.Unbind();
        GroupMenuUI->GroupCreateSignature.Unbind();
    }
    else
    {
        bOpenGroupMenuUI = true;

        FWidgetTransform position = GroupMenuUI->GetRenderTransform();
        position.Translation.X = -3.f;
        position.Translation.Y = GroupRelativePosition.Y + 13.f;
        GroupMenuUI->SetRenderTransform(position);
        GroupMenuUI->SetVisibility(ESlateVisibility::Visible);
        GroupMenuUI->SetGroupSeq(SelectedGroup);
        GroupMenuUI->SetGroupName(SelectedGroupName);
        GroupMenuUI->GroupRemovedSignature.BindUObject(this, &UFriendListUI::RemoveGroup);
        GroupMenuUI->GroupCreateSignature.BindUObject(this, &UFriendListUI::OpenCreateGroupUI);
        GroupMenuUI->GroupRenameSignature.BindUObject(this, &UFriendListUI::OpenAndSetRenameUI);

        if (SelectedGroupName == RLRLITERAL.Friend_DefaultGroup)
        {
            GroupMenuUI->RenameGroupButton->SetIsEnabled(false);
        }
        else
        {
            GroupMenuUI->RenameGroupButton->SetIsEnabled(true);
        }
    }
}

void UFriendListUI::RemoveGroup(int OldGroupSeq)
{
    FriendTabWidget->RemoveGroup(OldGroupSeq);
}

void UFriendListUI::MoveGroup()
{
    OpenFriendMenuUI(true);
	if (bIsMoveGroupMessageBoxOpen)
	{
        if (FriendTabWidget->MoveGroupMessageBox)
        {
            FriendTabWidget->MoveGroupMessageBox->SetVisibility(ESlateVisibility::Hidden);
        }
        bIsMoveGroupMessageBoxOpen = false;
	}
    else
    {
        if (FriendTabWidget->MoveGroupMessageBox)
        {
            FriendTabWidget->MoveGroupMessageBox->SetVisibility(ESlateVisibility::Visible);
        }
        bIsMoveGroupMessageBoxOpen = true;
    }
}

void UFriendListUI::OpenAndSetRenameUI(bool bOpen, FString CurrentGroupName, int32 CurrentGroupSeq)
{
    OpenGroupRenameUI(bOpen);

    bOpenGroupMenuUI = true;
    OpenGroupMenuUI();
    
    RenameGroupMessageBox->SetGroupSeq(CurrentGroupSeq);
    RenameGroupMessageBox->SetCurrentGroupName(FText::FromString(CurrentGroupName));
}

void UFriendListUI::SetFriendRequestMessageBox(FString& PlayerName)
{
    AsyncTask(ENamedThreads::GameThread, [this, PlayerName]()
        {
            // MessageBox 생성
            UFriendRequestMessageBox* FriendRequestMessageBox = CreateWidget<UFriendRequestMessageBox>(GetWorld(), FriendRequestMessageBoxClass);
            if (FriendRequestMessageBox)
            {
                FriendRequestMessageBox->InitializeWidget(PlayerName);
                FriendRequestMessageBox->AddToViewport();

                GetWorld()->GetTimerManager().SetTimer(
                    FriendRequestMessageBoxTimerHandle,
                    FTimerDelegate::CreateWeakLambda(this, [FriendRequestMessageBox]()
                        {
                            if (IsValid(FriendRequestMessageBox))
                            {
                                FriendRequestMessageBox->RemoveFromParent();
                            }
                        }),
                    10.0f,
                    false
                );
            }
        });
}

void UFriendListUI::SetMoveGroupMessageOpenState(bool bOpen)
{
    bIsMoveGroupMessageBoxOpen = bOpen;
}

void UFriendListUI::OpenFriendInfoUI(int FriendSeq)
{
    if (bOpenFriendInfoUI)
    {
        bOpenFriendInfoUI = false;
        FriendInfoUI->CloseUI();
    }
    else
    {
        bOpenFriendInfoUI = true;
        if (FriendInfoUI)
        {
            FriendInfoUI->SetPosition((FVector2D(960.f, 540.f)));
            FriendInfoUI->OpenUI();
            FriendInfoUI->SetFriendDetails(SelectedFriend);
        }
    }
}

FVector2D UFriendListUI::GetButtonRightCenter(FVector2D ViewportSize)
{
    float ViewportWidth = ViewportSize.X;
    float ViewportHeight = ViewportSize.Y;

    FVector2D BottomRightCenter;
    BottomRightCenter.X = (ViewportWidth / 2) + (ViewportWidth / 4);
    BottomRightCenter.Y = (ViewportHeight / 2) + (ViewportHeight / 4);

    return BottomRightCenter;
}

FReply UFriendListUI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (IsInUI(InGeometry, InMouseEvent))
    {
        return FReply::Handled();
    }
    return FReply::Unhandled();
}

bool UFriendListUI::IsInUI(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FVector2D LocalMousePosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
    return InGeometry.IsUnderLocation(InMouseEvent.GetScreenSpacePosition());
}