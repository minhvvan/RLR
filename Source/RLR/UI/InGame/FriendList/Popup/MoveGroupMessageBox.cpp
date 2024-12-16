// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/Popup/MoveGroupMessageBox.h"
#include "Components/Button.h"

void UMoveGroupMessageBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddUniqueDynamic(this, &UMoveGroupMessageBox::ConfirmButtonClicked);
	}
	if (CancelButton)
	{
		CancelButton->OnClicked.AddUniqueDynamic(this, &UMoveGroupMessageBox::CancelButtonClicked);
	}
}

void UMoveGroupMessageBox::ConfirmButtonClicked()
{
	OnConfirmButtonClicked.Broadcast();
}

void UMoveGroupMessageBox::CancelButtonClicked()
{
	OnCancelButtonClicked.Broadcast();
}