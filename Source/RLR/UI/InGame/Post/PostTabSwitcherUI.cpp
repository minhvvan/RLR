// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostTabSwitcherUI.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/WidgetSwitcher.h"
#include "Components/WidgetSwitcher.h"
#include "Structs/ItemStructs.h"
#include "Structs/CommunicationStructs.h"
#include "GameManager/PostalManager.h"
#include "GameManager/GameManager.h"

void UPostTabSwitcherUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPostTabSwitcherUI::OnReceivedPostButtonClicked()
{
    SwitchToTab(0);
}

void UPostTabSwitcherUI::OnSentPostButtonClicked()
{
    SwitchToTab(1);
}

void UPostTabSwitcherUI::OnWritePostButtonClicked()
{
	SwitchToTab(2);
}

void UPostTabSwitcherUI::SwitchToTab(int32 TabIndex)
{
    if (PostContentSwitcher)
    {
        PostContentSwitcher->SetActiveWidgetIndex(TabIndex);
    }
}

//void UPostTabSwitcherUI::UpdateReceivedPostList(const TArray<FPost>& ReceivedPosts)
//{
//    if (ReceivedPostListView)
//    {
//        ReceivedPostListView->ClearListItems();
//        for (const FPost& Post : ReceivedPosts)
//        {
//            /* FPost를 보여줄 클래스 하나 생성하기 */
//            //UPostDataObject* PostObject = NewObject<UPostDataObject>(this);
//            //PostObject->PostData = Post;
//            //ReceivedPostListView->AddItem(PostObject);
//        }
//    }
//}
//
//void UPostTabSwitcherUI::UpdateSentPostList(const TArray<FPost>& SentPosts)
//{
//    if (SentPostListView)
//    {
//        SentPostListView->ClearListItems();
//        for (const FPost& Post : SentPosts)
//        {
//            //UPostDataObject* PostObject = NewObject<UPostDataObject>(this);
//            //PostObject->PostData = Post;
//            //SentPostListView->AddItem(PostObject);
//        }
//    }
//}
