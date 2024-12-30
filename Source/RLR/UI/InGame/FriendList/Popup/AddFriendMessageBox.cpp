// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/Popup/AddFriendMessageBox.h"
#include "GameManager/LiteralManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameManager.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UAddFriendMessageBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayerNameInputText)
	{
		PlayerNameInputText->OnTextChanged.AddUniqueDynamic(this, &UAddFriendMessageBox::OnFriendNameTextChanged);
	}
	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddUniqueDynamic(this, &UAddFriendMessageBox::OnConfirmButtonClicked);
	}
	if (CancelButton)
	{
		CancelButton->OnClicked.AddUniqueDynamic(this, &UAddFriendMessageBox::OnCancelButtonClicked);
	}
}

void UAddFriendMessageBox::OnFriendNameTextChanged(const FText& Text)
{
	FString FriendName = Text.ToString();
}

void UAddFriendMessageBox::OnConfirmButtonClicked()
{
	if (GroupListDropDownBox->GetSelectedOption().IsEmpty())
	{
		GroupListDropDownBox->SetSelectedOption(RLRLITERAL.Friend_DefaultGroup);
	}

	/* GroupListDropDownBox->GetSelectedOption()도 서버에 보내주기 */
	GameInstance->GetNetworkManager()->SendRequestFriend(PlayerNameInputText->GetText().ToString());

	OnCloseRequestUISignature.Broadcast(true);
	InitComponents();
}

void UAddFriendMessageBox::OnCancelButtonClicked()
{
	OnCloseRequestUISignature.Broadcast(true);
	InitComponents();
}

void UAddFriendMessageBox::InitComponents()
{
	PlayerNameInputText->SetText(FText::FromString(RLRLITERAL.NullptrOption));
	FString CurrentSelected = GroupListDropDownBox->GetSelectedOption();
	GroupListDropDownBox->RemoveOption(CurrentSelected);
	GroupListDropDownBox->AddOption(CurrentSelected);

	GroupListDropDownBox->SetSelectedOption(RLRLITERAL.Friend_DefaultGroup);
}