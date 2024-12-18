// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/Popup/MoveGroupMessageBox.h"
#include "Components/ComboBoxString.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "GameManager/LiteralManager.h"

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
	if (GroupListDropDownBox->GetSelectedOption().IsEmpty())
	{
		GroupListDropDownBox->SetSelectedOption(RLRLITERAL.Friend_DefaultGroup);
	}
	OnConfirmButtonClicked.Broadcast();
}

void UMoveGroupMessageBox::CancelButtonClicked()
{
	OnCancelButtonClicked.Broadcast();

	FString CurrentSelected = GroupListDropDownBox->GetSelectedOption();
	GroupListDropDownBox->RemoveOption(CurrentSelected);
	GroupListDropDownBox->AddOption(CurrentSelected);

	GroupListDropDownBox->SetSelectedOption(RLRLITERAL.Friend_DefaultGroup);
}