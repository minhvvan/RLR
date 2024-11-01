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
    FriendButtons.Empty();
    
    for (UWidget* child : FriendRequestScrollBox->GetAllChildren())
    {
        if (child)
        {
            FriendRequestScrollBox->RemoveChild(child);
        }
    }
}