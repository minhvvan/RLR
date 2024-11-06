// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendConnectionStatusUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UFriendConnectionStatusUI::NativeConstruct()
{
	if (PlayerStatusOnline)
	{
		PlayerStatusOnline->OnClicked.AddUniqueDynamic(this, &UFriendConnectionStatusUI::SetPlayerStatusOnline);
	}
	if (PlayerStatusOffline)
	{
		PlayerStatusOffline->OnClicked.AddUniqueDynamic(this, &UFriendConnectionStatusUI::SetPlayerStatusOffline);
	}
	if (PlayerStatusAway)
	{
		PlayerStatusAway->OnClicked.AddUniqueDynamic(this, &UFriendConnectionStatusUI::SetPlayerStatusAway);
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