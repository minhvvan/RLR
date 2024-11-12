// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendRequestTabWidget.h"
#include "UI/InGame/FriendList/FriendButtonUI.h"
#include "Components/ScrollBox.h"

void UFriendRequestTabWidget::NativeConstruct()
{
	
}

void UFriendRequestTabWidget::UpdateFriendRequestTab(TMap<int32, FString> RequestFriendData)
{
    ClearFriendRequestList();
    for (const TPair<int32, FString>& Pair : RequestFriendData)
    {
        AddFriendButton(Pair.Key, Pair.Value);
    }
}

void UFriendRequestTabWidget::AddFriendButton(int32 friendSeq, FString friendName)
{
    AsyncTask(ENamedThreads::GameThread, [this, friendSeq, friendName]()
        {
            UFriendButtonUI* FriendButtonUI = CreateWidget<UFriendButtonUI>(this, FriendButtonUIClass);
            FriendButtonUI->SetFriendInfo(friendSeq, friendName);
            FriendRequestScrollBox->AddChild(FriendButtonUI);
            FriendButtons.Add(friendSeq, FriendButtonUI);
        });
}

void UFriendRequestTabWidget::ClearFriendRequestList()
{
    if (!IsInGameThread())
    {
        AsyncTask(ENamedThreads::GameThread, [this]()
            {
                /* Game Thread 에서 재호출 */
                ClearFriendRequestList();
            });
        return;
    }

    // 실제 Clear 작업
    FriendButtons.Empty();
    FriendRequestScrollBox->ClearChildren();
}