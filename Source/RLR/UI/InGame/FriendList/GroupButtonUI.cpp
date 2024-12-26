// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/GroupButtonUI.h"
#include "UI/InGame/FriendList/FriendButtonMenu.h"
#include "UI/InGame/FriendList/FriendGroupDragDropOperation.h"
#include "UI/InGame/FriendList/FriendListUI.h"
#include "Components/VerticalBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UGroupButtonUI::NativeConstruct()
{
    Super::NativeConstruct();

    if (GroupButton)
    {
        GroupButton->OnClicked.AddUniqueDynamic(this, &UGroupButtonUI::OnGroupButtonClicked);
    }
    if (UScrollBox* ParentBox = Cast<UScrollBox>(GetParent()))
    {
        SetIsFocusable(true);
    }
}

void UGroupButtonUI::SetGroupInfo(int NewGroupSeq, FString NewGroupName)
{
    GroupSeq = NewGroupSeq;
    GroupName = NewGroupName;
    GroupNameText->SetText(FText::FromString(GroupName));
}

FString UGroupButtonUI::GetGroupName()
{
    return GroupName;
}

void UGroupButtonUI::OnGroupButtonClicked()
{
    // Toggle Children of GroupContainer
    if (GroupContainer)
    {
        if (GroupContainer->GetVisibility() == ESlateVisibility::Collapsed)
        {
            GroupContainer->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            GroupContainer->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
	else
	{
        // GroupList에 있는 GroupButtonUI일때
        if (bIsInGroupList)
        {
		    GroupClickedOnList.Execute(this);
            // Close friendButtonMenu
            if (FriendListUI)
            {
                FriendListUI->FriendMenuUI->SetVisibility(ESlateVisibility::Hidden);
            }
        }
	}
}

FReply UGroupButtonUI::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    // GroupOrderList에 있는 GroupButtonUI일때
    if (bIsInGroupOrderList)
    {
        Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

        FVector2D MousePos = InMouseEvent.GetScreenSpacePosition();
        DragOffset = InGeometry.AbsoluteToLocal(MousePos);

        FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

        return ReplyResult.NativeReply;
    }
    return FReply::Unhandled();
}

FReply UGroupButtonUI::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
    if (MouseEvent.IsControlDown() && MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
    {
        if (GroupButton && GroupButton->GetCachedGeometry().IsUnderLocation(MouseEvent.GetScreenSpacePosition()))
        {
            // friendScrollBox에 있는 그룹 버튼을 우클릭 시 메뉴 표시
            if (OnGroupRightClicked.IsBound() && GroupContainer)
            {
                FVector2D AbsolutePosition = GetCachedGeometry().LocalToAbsolute(FVector2D::ZeroVector);
                OnGroupRightClicked.Execute(AbsolutePosition, this);  // 델리게이트 호출
            }
            return FReply::Handled();
        }
    }

    return FReply::Unhandled();
}

void UGroupButtonUI::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

    UFriendGroupDragDropOperation* DragOperation = Cast<UFriendGroupDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(DragDropOperationClass));
    SetVisibility(ESlateVisibility::HitTestInvisible);
    
    DragOperation->DefaultDragVisual = this;
    DragOperation->Pivot = EDragPivot::MouseDown;
    DragOperation->Payload = this;

    DragOperation->GroupData = GroupData;
    DragOperation->DragOffset = DragOffset;

    OutOperation = DragOperation;
}

bool UGroupButtonUI::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    if (bIsInGroupOrderList)
    {
        Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

        UFriendGroupDragDropOperation* Operation = Cast<UFriendGroupDragDropOperation>(InOperation);
        if (IsValid(Operation) == false)
            return false;

        UGroupButtonUI* DraggedButton = Cast<UGroupButtonUI>(InOperation->Payload);
        if (IsValid(DraggedButton) == false) 
            return false;
        if(!DraggedButton->bIsInGroupOrderList)
            return false;
        OnGroupButtonDropped.Broadcast(DraggedButton, this);

        return true;
    }
    return false;
}

void UGroupButtonUI::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

    // 버튼을 다시 보이도록 설정
    SetVisibility(ESlateVisibility::Visible);
}