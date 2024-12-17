// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendTabWidget.h"
#include "UI/InGame/FriendList/FriendRequestUI.h"
#include "UI/InGame/FriendList/FriendButtonMenu.h"
#include "UI/InGame/FriendList/FriendInformation.h"
#include "UI/InGame/FriendList/FriendButtonUI.h"
#include "UI/InGame/FriendList/GroupButtonUI.h"
#include "UI/InGame/FriendList/FriendListUI.h"
#include "UI/InGame/FriendList/FriendConnectionStatusUI.h"
#include "UI/InGame/FriendList/Popup/MoveGroupMessageBox.h"
#include "UI/InGame/FriendList/Popup/AddFriendMessageBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/EditableText.h"
#include "Components/ComboBoxString.h"
#include "Components/VerticalBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Components/Button.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/FriendManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/LiteralManager.h"
#include "RLR.h"

void ClearChildren(UWidget* Container)
{
    if (UScrollBox* ScrollBox = Cast<UScrollBox>(Container))
    {
        // ScrollBox에서 모든 자식 제거
        TArray<UWidget*> ChildrenToRemove = ScrollBox->GetAllChildren();
        for (UWidget* Child : ChildrenToRemove)
        {
            if (Child)
            {
                ScrollBox->RemoveChild(Child);
            }
        }
    }
    else if (UVerticalBox* VerticalBox = Cast<UVerticalBox>(Container))
    {
        // VerticalBox에서 모든 자식 제거
        while (VerticalBox->GetChildrenCount() > 0)
        {
            VerticalBox->RemoveChildAt(0);
        }
    }
}


void UFriendTabWidget::NativeConstruct()
{
    if (FriendRequestButton)
    {
        FriendRequestButton->OnClicked.AddUniqueDynamic(this, &UFriendTabWidget::RequestFriendButtonClicked);
    }
    if (PlayerStatusSetting)
    {
        PlayerStatusSetting->OnClicked.AddUniqueDynamic(this, &UFriendTabWidget::OnPlayerStatusSettingClicked);
    }
    if (GroupCreationButton)
    {
        GroupCreationButton->OnClicked.AddUniqueDynamic(this, &UFriendTabWidget::AddGroupButtonClicked);
    }
    if (SearchFriendUI)
    {
        SearchFriendUI->OnTextChanged.AddUniqueDynamic(this, &UFriendTabWidget::SearchFriend);
    }
    if (ChangeGroupOrderButton)
    {
        ChangeGroupOrderButton->OnClicked.AddUniqueDynamic(this, &UFriendTabWidget::ChangeGroupOrder);
    }
    if (MoveGroupMessageBox)
    {
        MoveGroupMessageBox->OnConfirmButtonClicked.AddUniqueDynamic(this, &UFriendTabWidget::UpdateGroupInfoUI);
        MoveGroupMessageBox->OnCancelButtonClicked.AddUniqueDynamic(this, &UFriendTabWidget::CancelMoveGroup);
    }
}

void UFriendTabWidget::RequestFriendButtonClicked()
{
    // FriendListUI에서 처리하도록 변경
    if (FriendListUI)
    {
        FriendListUI->OpenFriendRequestUI(false);
    }
}

void UFriendTabWidget::UpdateFriendTab(const TArray<FFriendGroupResult>& groupData)
{
    ClearFriendList();
    AddDefaultGroup(groupData);
    for (int i = 0; i < groupData.Num(); i++)
    {
        AddGroupButton(i, groupData[i].GroupName);

        for (int j = 0; j < groupData[i].FriendSeq.Num(); j++)
        {
            AddFriendButton(groupData[i].FriendSeq[j], i, groupData[i].FriendName[j]);
        }
    }
}

void UFriendTabWidget::OnPlayerStatusSettingClicked()
{
    AsyncTask(ENamedThreads::GameThread, [this]()
        {
            if (FriendConnectionStatusClass)
            {
                UFriendConnectionStatusUI* FriendConnectionStatusUI = CreateWidget<UFriendConnectionStatusUI>(this, FriendConnectionStatusClass);
                                
                FVector2D DesiredSize(120, 95);
                FriendConnectionStatusUI->SetDesiredSizeInViewport(DesiredSize);

                FVector2D ButtonAbsolutePosition = PlayerStatusSetting->GetCachedGeometry().GetAbsolutePosition();
                FriendConnectionStatusUI->SetPositionInViewport(ButtonAbsolutePosition);

                FriendConnectionStatusUI->AddToViewport();

                FriendConnectionStatusUI->OnPlayerStatusChangedDelegate.AddDynamic(this, &UFriendTabWidget::UpdatePlayerConnectionStatus);
            }
        });
}

void UFriendTabWidget::AddGroupButtonClicked()
{
    // 그룹 명 입력할 위젯 open하도록 friendlistui에 전달    
    if (FriendListUI)
    {
        FriendListUI->OpenAddGroupUI(false);
    }

}
// 그룹 이동
void UFriendTabWidget::GroupClickedOnGroupList(UGroupButtonUI* GroupButtonUI)
{
    if (!GroupButtonUI)
    {
        return;
    }

    SelectedGroup = GroupButtonUI->GetGroupSeq();
    UGroupButtonUI* GroupMoveTo = GroupButtons.FindRef(GroupButtonUI->GetGroupSeq());
    UFriendButtonUI* SelectedFriendButton = FriendButtons.FindRef(SelectedFriend);

    if (!SelectedFriendButton)
    {
        return;
    }

    if (SelectedFriendButton->GetGroupSeq() != SelectedGroup)
    {
        // 현재 그룹에서 친구 버튼 제거
        for (const TPair<int32, UGroupButtonUI*>& Pair : GroupButtons)
        {
            if (Pair.Value && Pair.Value->GetGroupSeq() == SelectedFriendButton->GetGroupSeq())
            {
                if (Pair.Value->GroupContainer)
                {
                    Pair.Value->GroupContainer->RemoveChild(SelectedFriendButton);
                    break;
                }
            }
        }

        // 새 그룹에 친구 버튼 추가
        if (GroupMoveTo->GroupContainer)
        {
            GroupMoveTo->GroupContainer->AddChild(SelectedFriendButton);
            SelectedFriendButton->SetGroupSeq(SelectedGroup);
        }
    }

    // 친구 그룹 이동 요청 전송
    if (GameInstance && GameInstance->GetNetworkManager())
    {
        GameInstance->GetNetworkManager()->SendMoveFriendInGroup(SelectedFriend, SelectedGroup);
    }
}

void UFriendTabWidget::UpdatePlayerConnectionStatus(FText StatusText)
{
    PlayerStatusText->SetText(StatusText);
}

void UFriendTabWidget::AddFriendButton(int friendSeq, int groupSeq, FString friendName)
{
    AsyncTask(ENamedThreads::GameThread, [this, friendSeq, groupSeq, friendName]()
        {
            if (FriendScrollBox && FriendButtonUIClass && GroupButtons.Contains(groupSeq))
            {
                UFriendButtonUI* FriendButtonUI = CreateWidget<UFriendButtonUI>(this, FriendButtonUIClass);
                FriendButtonUI->SetFriendInfo(friendSeq, friendName);
                FriendButtonUI->OnFriendRequestButtonClick.AddUObject(this, &UFriendTabWidget::OnFriendButtonClicked);
                FriendButtonUI->OnFriendRightClicked.BindUObject(this, &UFriendTabWidget::OnFriendRightClick);
                /*FriendScrollBox->AddChild(FriendButtonUI);*/
                FriendButtons.Add(friendSeq, FriendButtonUI);

                if (FriendButtonUI->GetParent() != nullptr)
                {
                    FriendButtonUI->RemoveFromParent();
                }
                // 새로운 부모에 추가
                UGroupButtonUI* GroupButton = GroupButtons.FindRef(groupSeq);
                if (GroupButton)
                {
                    FriendButtonUI->SetGroupSeq(groupSeq);
                    GroupButton->GroupContainer->AddChild(FriendButtonUI);
                }
            }
        });
}

void UFriendTabWidget::AddGroupButton(int groupSeq, FString groupName)
{
    AsyncTask(ENamedThreads::GameThread, [this, groupSeq, groupName]()
        {
            if (FriendScrollBox && GroupButtonUIClass && !GroupButtons.Contains(groupSeq))
            {
                for (const TPair<int32, UGroupButtonUI*>& pair : GroupButtons)
                {
                    if (pair.Value && pair.Value->GetGroupName().Equals(groupName))
                    {
                        return;
                    }
                }

                UGroupButtonUI* GroupButtonUI = CreateWidget<UGroupButtonUI>(this, GroupButtonUIClass);
                GroupButtonUI->SetGroupInfo(groupSeq, groupName);
                GroupButtonUI->OnGroupRightClicked.BindUObject(this, &UFriendTabWidget::OnGroupRightClick);
                FriendScrollBox->AddChild(GroupButtonUI);
                GroupButtons.Add(groupSeq, GroupButtonUI);

                if (MoveGroupMessageBox->GroupListDropDownBox)
				{
                    MoveGroupMessageBox->GroupListDropDownBox->AddOption(groupName);
                }

                if (FriendListUI->AddFriendMessageBox->GroupListDropDownBox)
                {
                    FriendListUI->AddFriendMessageBox->GroupListDropDownBox->AddOption(groupName);
                }

                if (GroupOrderScrollBox)
                {
                    UGroupButtonUI* GroupButtonOrderList = CreateWidget<UGroupButtonUI>(this, GroupButtonInGroupOrderClass);
					GroupButtonOrderList->SetGroupInfo(groupSeq, groupName);
                    GroupButtonOrderList->OnGroupButtonDropped.AddDynamic(this, &UFriendTabWidget::ReorderGroups);
					GroupOrderScrollBox->AddChild(GroupButtonOrderList);
                    OrderedGroupButtons.Add(GroupButtonOrderList);
                }
            }
        });
}

void UFriendTabWidget::AddDefaultGroup(const TArray<FFriendGroupResult>& groupData)
{
    for (const FFriendGroupResult groupDatum : groupData)
    {
        if(groupDatum.GroupName.Equals(RLRLITERAL.Friend_DefaultGroup)) return;
    }
    std::string DefaultGroupName = TCHAR_TO_UTF8(*FString(RLRLITERAL.Friend_DefaultGroup));
    GameInstance->GetNetworkManager()->SendCreateFriendGroup(DefaultGroupName);
}

void UFriendTabWidget::OnFriendButtonClicked(int friendSeq, UFriendButtonUI* FriendButtonUI)
{
    if (friendSeq == SelectedFriend) return;
    FriendButtonUI->SetButtonState(true);
    if (FriendButtons.Contains(SelectedFriend))
    {
        UFriendButtonUI* PrevButton = *FriendButtons.Find(SelectedFriend);
        if (PrevButton)
        {
            PrevButton->SetButtonState(false);
        }
    }
    SelectedFriend = friendSeq;
}

void UFriendTabWidget::OnFriendRightClick(FVector2D AbsolutePosition, UFriendButtonUI* FriendButtonUI)
{
    // UFriendListUI의 OnFriendRightMouseClicked를 호출합니다.
    // 이를 위해 UFriendListUI에 대한 참조가 필요합니다.
    if (FriendListUI)
    {
        FriendListUI->OnFriendRightMouseClicked(AbsolutePosition, FriendButtonUI);
    }
    SelectedFriend = FriendButtonUI->GetFriendSeq();

    if (MoveGroupMessageBox->GroupListDropDownBox)
    {
        UFriendButtonUI* SelectedFriendButton = FriendButtons.FindRef(SelectedFriend);
        UGroupButtonUI* SelectedGroupButton = GroupButtons.FindRef(SelectedFriendButton->GetGroupSeq());
        MoveGroupMessageBox->GroupListDropDownBox->SetSelectedOption(SelectedGroupButton->GetName());
        MoveGroupMessageBox->PlayerNameInputText->SetText(FText::FromString(SelectedFriendButton->GetFriendName()));
    }
}

void UFriendTabWidget::OnGroupRightClick(FVector2D AbsolutePosition,UGroupButtonUI* GroupButtonUI)
{
    if (FriendListUI)
    {
        FriendListUI->OnGroupRightMouseClicked(AbsolutePosition, GroupButtonUI);
    }
    SelectedGroup = GroupButtonUI->GetGroupSeq();
}

// 그룹 삭제
void UFriendTabWidget::RemoveGroup(int OldGroupSeq)
{
    // 플레이어를 담을 기본그룹 찾기
    UGroupButtonUI* defaultGroupButton = nullptr;
    for (const TPair<int32, UGroupButtonUI*>& pair : GroupButtons)
    {
        if (pair.Value && pair.Value->GetGroupName().Equals(RLRLITERAL.Friend_DefaultGroup))
        {
            defaultGroupButton = pair.Value;
            break;
        }
    }
    // default group은 삭제되지 않도록 함
    if (defaultGroupButton)
    {
        if(defaultGroupButton->GetGroupSeq() == OldGroupSeq) return;
    }

    UGroupButtonUI* GroupRemoved = GroupButtons.FindRef(OldGroupSeq);

    // 그룹 내 친구 버튼 삭제
    for (UWidget* child : GroupRemoved->GroupContainer->GetAllChildren())
    {
        if (UFriendButtonUI* friendButton = Cast<UFriendButtonUI>(child))
        {
            friendButton->RemoveFromParent();
            if (defaultGroupButton)
            {
                defaultGroupButton->GroupContainer->AddChild(friendButton);
                friendButton->SetGroupSeq(defaultGroupButton->GetGroupSeq());
                GameInstance->GetNetworkManager()->SendMoveFriendInGroup(friendButton->GetFriendSeq(), defaultGroupButton->GetGroupSeq());
            }
        }
    }

    // 그룹 버튼 삭제
    FriendScrollBox->RemoveChild(GroupRemoved);
    if (MoveGroupMessageBox->GroupListDropDownBox)
    {
        MoveGroupMessageBox->GroupListDropDownBox->RemoveOption(GroupRemoved->GetGroupName());
        GroupButtons.Remove(OldGroupSeq);
    }

    if (GroupOrderScrollBox)
    {
        GroupOrderScrollBox->RemoveChild(GroupRemoved);
    }
    FriendListUI->OpenGroupMenuUI();
}

void UFriendTabWidget::SearchFriend(const FText& Text)
{
    if (Text.IsEmpty())
    {
        for (const TPair<int32, UGroupButtonUI*>& pair : GroupButtons)
        {
            if (pair.Value->GroupContainer)
            {
                TArray<UWidget*> Children = pair.Value->GroupContainer->GetAllChildren();
                for (UWidget* Child : Children)
                {
                    if (UFriendButtonUI* FriendButton = Cast<UFriendButtonUI>(Child))
                    {
                        FriendButton->SetVisibility(ESlateVisibility::Visible);
                    }
                }
            }
        }
        return; // Return early as no further filtering is needed
    }

    for (const TPair<int32, UGroupButtonUI*>& pair : GroupButtons)
    {
        if (pair.Value->GroupContainer)
        {
            TArray<UWidget*> ChildrenToRemove = pair.Value->GroupContainer->GetAllChildren();
            for (UWidget* Child : ChildrenToRemove)
            {
                if (UFriendButtonUI* friendButton = Cast<UFriendButtonUI>(Child))
                {
                    if (friendButton->GetFriendName().Equals(Text.ToString()))
                    {
                        // 이 friendButton을 제외한 모든 Child들은 EVisibility::Collapse로 설정하기
                        friendButton->SetVisibility(ESlateVisibility::Visible);
                    }
                    else
                    {
                        friendButton->SetVisibility(ESlateVisibility::Collapsed);
                    }
                }
            }
        }
    }
}

void UFriendTabWidget::ChangeGroupOrder()
{
    if (bGroupOrderOpen)
    {
        bGroupOrderOpen = false;
        GroupOrderSizeBox->SetVisibility(ESlateVisibility::Hidden);
    }
    else
    {
        bGroupOrderOpen = true;
        if (GroupOrderScrollBox)
        {
            GroupOrderSizeBox->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void UFriendTabWidget::ClearFriendList()
{
    if (!IsInGameThread())
    {
        AsyncTask(ENamedThreads::GameThread, [this]()
            {
                ClearFriendList();
            });
        return;
    }

    // FriendScrollBox와 GroupOrderScrollBox 자식 제거
    ClearChildren(FriendScrollBox);
    ClearChildren(GroupOrderScrollBox);

    // GroupButtons의 각 GroupContainer에서 자식 제거
    for (const TPair<int32, UGroupButtonUI*>& pair : GroupButtons)
    {
        if (pair.Value && pair.Value->GroupContainer)
        {
            ClearChildren(pair.Value->GroupContainer);
        }
    }

    // FriendMenuUI의 GroupListBox 자식 제거
    MoveGroupMessageBox->GroupListDropDownBox->ClearOptions();

    GroupButtons.Empty();
    FriendButtons.Empty();
    OrderedGroupButtons.Empty();
}

void UFriendTabWidget::UpdateGroupInfoUI()
{
    FString SelectedGroupName = MoveGroupMessageBox->GroupListDropDownBox->GetSelectedOption();
    UGroupButtonUI* SelectedGroupButton =  nullptr;
    for (const TPair<int32, UGroupButtonUI*>& Pair : GroupButtons)
    {
        if (Pair.Value && Pair.Value->GetGroupName() == SelectedGroupName)
        {
            SelectedGroupButton = Pair.Value;
            break;
        }
    }

    for (const TPair<int32, UGroupButtonUI*>& Pair : GroupButtons)
    {
        if (SelectedGroupButton->GetGroupSeq() == Pair.Key)
        {
            GroupClickedOnGroupList(Pair.Value);
            break;
        }
    }
    MoveGroupMessageBox->SetVisibility(ESlateVisibility::Hidden);
    FriendListUI->SetMoveGroupMessageOpenState(false);
}

void UFriendTabWidget::CancelMoveGroup()
{
    MoveGroupMessageBox->SetVisibility(ESlateVisibility::Hidden);
    FriendListUI->SetMoveGroupMessageOpenState(false);
}

void UFriendTabWidget::ReorderGroups(UGroupButtonUI* DraggedButton, UGroupButtonUI* TargetButton)
{
    int32 DraggedIndex = OrderedGroupButtons.IndexOfByKey(DraggedButton);
    int32 TargetIndex = OrderedGroupButtons.IndexOfByKey(TargetButton);

    if (DraggedIndex != INDEX_NONE && TargetIndex != INDEX_NONE)
    {
        int32 TempGroupSeq = DraggedButton->GetGroupSeq();
        DraggedButton->SetGroupInfo(TargetButton->GetGroupSeq(), DraggedButton->GetGroupName());
        TargetButton->SetGroupInfo(TempGroupSeq, TargetButton->GetGroupName());

        // OrderedGroupButtons 배열에서 DraggedButton과 TargetButton의 위치 교환
        OrderedGroupButtons[DraggedIndex] = TargetButton;
        OrderedGroupButtons[TargetIndex] = DraggedButton;

        // Reorder the widgets in the scroll box
        GroupOrderScrollBox->ClearChildren();
        for (UGroupButtonUI* GroupButton : OrderedGroupButtons)
        {
            GroupOrderScrollBox->AddChild(GroupButton);
        }

        GameInstance->GetNetworkManager()->SendMoveFriendGroup(DraggedButton->GetGroupSeq(), TargetButton->GetGroupSeq());
    }
}