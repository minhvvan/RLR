// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/GroupCreationUI.h"
#include "Structs/UtilStructs.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "Components/EditableText.h"
#include "Components/Button.h"

void UGroupCreationUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddUniqueDynamic(this, &UGroupCreationUI::ConfirmButtonClicked);
	}
	if (CancelButton)
	{
		CancelButton->OnClicked.AddUniqueDynamic(this, &UGroupCreationUI::CancelButtonClicked);
	}
	if (GroupNameText)
	{
		GroupNameText->OnTextChanged.AddUniqueDynamic(this, &UGroupCreationUI::HandleTextChanged);
	}
}

void UGroupCreationUI::ConfirmButtonClicked()
{
	OnGroupCreationOpen.Broadcast(true);
	std::string GroupName = TCHAR_TO_UTF8(*GroupNameText->GetText().ToString());
	GameInstance->GetNetworkManager()->SendCreateFriendGroup(GroupName);
}

void UGroupCreationUI::CancelButtonClicked()
{
	OnGroupCreationOpen.Broadcast(true);
}

void UGroupCreationUI::HandleTextChanged(const FText& Text)
{
	FString CurrentText = Text.ToString();

	if (CurrentText.Len() > maxCharacters)
	{
		GroupNameText->SetText(FText::FromString(CurrentText.Left(maxCharacters)));
	}
}