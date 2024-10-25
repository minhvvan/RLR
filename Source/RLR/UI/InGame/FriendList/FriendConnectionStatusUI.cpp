// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendConnectionStatusUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UFriendConnectionStatusUI::NativeConstruct()
{
	if (PlayerStatusOnline)
	{
		PlayerStatusOnline->OnClicked.AddDynamic(this, &UFriendConnectionStatusUI::SetPlayerStatusOnline);
	}
	if (PlayerStatusOffline)
	{
		PlayerStatusOffline->OnClicked.AddDynamic(this, &UFriendConnectionStatusUI::SetPlayerStatusOffline);
	}
	if (PlayerStatusAway)
	{
		PlayerStatusAway->OnClicked.AddDynamic(this, &UFriendConnectionStatusUI::SetPlayerStatusAway);
	}
}

void UFriendConnectionStatusUI::SetPlayerStatusOnline()
{
	OnPlayerStatusChangedDelegate.Broadcast(PlayerStatusOnlineText->GetText());
	this->RemoveFromParent();
}

void UFriendConnectionStatusUI::SetPlayerStatusOffline()
{
	OnPlayerStatusChangedDelegate.Broadcast(PlayerStatusOfflineText->GetText());
	this->RemoveFromParent();
}

void UFriendConnectionStatusUI::SetPlayerStatusAway()
{
	OnPlayerStatusChangedDelegate.Broadcast(PlayerStatusAwayText->GetText());
	this->RemoveFromParent();
}