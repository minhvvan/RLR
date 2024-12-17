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
	if (GroupListDropDownBox)
	{
		GroupListDropDownBox->AddOption(RLRLITERAL.Friend_DefaultGroup);
		GroupListDropDownBox->SetSelectedOption(RLRLITERAL.Friend_DefaultGroup);
		GroupListDropDownBox->OnSelectionChanged.AddUniqueDynamic(this, &UMoveGroupMessageBox::ChangedSelection);
	}
}

void UMoveGroupMessageBox::ConfirmButtonClicked()
{
	if (GroupListDropDownBox->GetSelectedOption().IsEmpty())
	{
		GroupListDropDownBox->SetSelectedOption(RLRLITERAL.Friend_DefaultGroup);
	}
	OnConfirmButtonClicked.Broadcast();
	Placeholder->SetVisibility(ESlateVisibility::Visible);
}

void UMoveGroupMessageBox::CancelButtonClicked()
{
	OnCancelButtonClicked.Broadcast();

	FString CurrentSelected = GroupListDropDownBox->GetSelectedOption();
	GroupListDropDownBox->RemoveOption(CurrentSelected);
	GroupListDropDownBox->AddOption(CurrentSelected);

	GroupListDropDownBox->SetSelectedOption(TEXT(""));
	Placeholder->SetVisibility(ESlateVisibility::Visible);
}

void UMoveGroupMessageBox::ChangedSelection(FString SelectedOption, ESelectInfo::Type SelectionType)
{
	if (!SelectedOption.IsEmpty())
	{
		Placeholder->SetVisibility(ESlateVisibility::Collapsed);
	}
}