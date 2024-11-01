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
		ConfirmButton->OnClicked.AddDynamic(this, &UGroupCreationUI::ConfirmButtonClicked);
	}
	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UGroupCreationUI::CancelButtonClicked);
	}
}

void UGroupCreationUI::ConfirmButtonClicked()
{
	std::string GroupName = TCHAR_TO_UTF8(*GroupNameText->GetText().ToString());
	GameInstance->GetNetworkManager()->SendCreateFriendGroup(GroupName);
}

void UGroupCreationUI::CancelButtonClicked()
{
	OnGroupCreationOpen.Broadcast(true);
}
