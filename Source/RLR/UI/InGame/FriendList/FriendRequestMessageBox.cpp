// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendRequestMessageBox.h"

#include "Components/TextBlock.h"

void UFriendRequestMessageBox::InitializeWidget(const FString& SenderName)
{
	if (SenderNameText)
	{
		SenderNameText->SetText(FText::FromString(SenderName));
	}
}