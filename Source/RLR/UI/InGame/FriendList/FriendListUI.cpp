// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendListUI.h"
#include "UI/InGame/FriendList/FriendTabWidget.h"
#include "UI/InGame/FriendList/FriendRequestUI.h"
#include "UI/InGame/FriendList/FriendRequestTabWidget.h"
#include "UI/InGame/FriendList/FriendButtonMenu.h"
#include "UI/InGame/FriendList/ExistingGroupList.h"
#include "UI/InGame/FriendList/GroupButtonMenu.h"
#include "UI/InGame/FriendList/FriendInformation.h"
#include "UI/InGame/FriendList/FriendButtonUI.h"
#include "UI/InGame/FriendList/GroupCreationUI.h"
#include "UI/InGame/FriendList/GroupButtonUI.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/FriendManager.h"
#include "Structs/UtilStructs.h"


void UFriendListUI::NativeConstruct()
{
    Super::NativeConstruct();

    SetUIType(EUIType::FRIEND_LIST_UI);
    SetUITag(FGameplayTagManager::Get().UI_FriendList);

    bOpenRequestUI = false;
    bOpenFriendMenuUI = false;
    bOpenFriendInfoUI = false;

    FriendTabWidget->FriendListUI = this;

    if (FriendTabButton)
    {
        FriendTabButton->OnClicked.AddDynamic(this, &UFriendListUI::OnFriendTabButtonClicked);
    }
    if (FriendRequestTabButton)
    {
        FriendRequestTabButton->OnClicked.AddDynamic(this, &UFriendListUI::OnFriendRequestTabButtonClicked);
    }
}

void UFriendListUI::Init()
{
}

void UFriendListUI::RefreshUI()
{
    // UI 새로고침 로직
    GameInstance->GetFriendManager()->InitializeFriendManager();
    if (FriendRequestUI)
    {
        FriendRequestUI->OnCloseRequestUISignature.RemoveAll(this);
        // FriendRequestUI가 닫힐 때 호출될 델리게이트에 바인딩
        FriendRequestUI->OnCloseRequestUISignature.AddDynamic(this, &UFriendListUI::OpenFriendRequestUI);
    }
    if (FriendTabWidget)
    {
        GameInstance->GetNetworkManager()->SendInfoFriend();
    }
	if (GroupCreationUI)
	{
        GroupCreationUI->OnGroupCreationOpen.RemoveAll(this);
		GroupCreationUI->OnGroupCreationOpen.AddDynamic(this, &UFriendListUI::OpenAddGroupUI);
	}
}

void UFriendListUI::OnFriendRightMouseClicked(FVector2D ButtonAbsolutePosition, UFriendButtonUI* FriendButtonUI)
{
    SelectedFriend = FriendButtonUI->GetFriendSeq();
    //FriendRelativePosition = ButtonAbsolutePosition - GetCachedGeometry().LocalToAbsolute(FVector2D::ZeroVector);
    FriendRelativePosition = GetCachedGeometry().AbsoluteToLocal(
        FriendButtonUI->GetCachedGeometry().LocalToAbsolute(FVector2D::Zero())
    );
    OpenFriendMenuUI();
}

void UFriendListUI::OnGroupRightMouseClicked(FVector2D ButtonAbsolutePosition, UGroupButtonUI* GroupButtonUI)
{
    SelectedGroup = GroupButtonUI->GetGroupSeq();
    //GroupRelativePosition = ButtonAbsolutePosition - GetCachedGeometry().LocalToAbsolute(FVector2D::ZeroVector);
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
        FriendRequestUI->SetVisibility(ESlateVisibility::Hidden);
    }
    else
    {
        bOpenRequestUI = true;
        if (FriendRequestUI)
        {
            FriendRequestUI->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void UFriendListUI::OpenFriendMenuUI()
{
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
            FriendMenuUI->SetFriendSeq(SelectedFriend);
        }
    }
}

void UFriendListUI::OpenAddGroupUI(bool bOpen)
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
        GroupMenuUI->GroupRemovedSignature.BindUObject(this, &UFriendListUI::RemoveGroup);
    }
}

void UFriendListUI::RemoveGroup(int OldGroupSeq)
{
    FriendTabWidget->RemoveGroup(OldGroupSeq);

	for (UWidget* Child : FriendMenuUI->GroupListUI->GroupListBox->GetAllChildren())
	{
		if (UGroupButtonUI* GroupButton = Cast<UGroupButtonUI>(Child))
		{
			if (GroupButton->GetGroupSeq() == OldGroupSeq)
			{
				FriendMenuUI->GroupListUI->GroupListBox->RemoveChild(GroupButton);
				break;
			}
		}
	}
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