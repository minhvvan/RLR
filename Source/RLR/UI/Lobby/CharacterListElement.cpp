// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/CharacterListElement.h"
#include "UI/Lobby/CharacterListUI.h"
#include "UI/Lobby/LobbyMainUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/NetworkManager.h"

#include "Components/ListView.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "GameManager/RLRStruct.h"


void UCharacterListElement::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UCharacterListElement* ListItem = Cast<UCharacterListElement>(ListItemObject);
	if (IsValid(ListItem) == false)
	{
		DEBUG_MESSAGE;
	}

	const FUserCharacter Data = ListItem->GetUserCharacterData();
	SetUserCharacterData(Data);
	RefreshUI();
}

void UCharacterListElement::NativeConstruct()
{
	Super::NativeConstruct();
	ConnectButton->OnClicked.AddUniqueDynamic(this, &UCharacterListElement::OnClickedConnectButton);
	ElementButton->OnClicked.AddUniqueDynamic(this, &UCharacterListElement::OnClickedElementButton);
}

void UCharacterListElement::RefreshUI()
{
	Super::RefreshUI();
	CharacterNameText->SetText(FText::FromString(UserCharacterData.NickName));
}

void UCharacterListElement::OnClickedConnectButton()
{
	if(UserCharacterData.UserSeq == -1)
		return;
	GetNetworkManager()->SendEnterGameFromLobbyReqeust(UserCharacterData);
}

void UCharacterListElement::OnClickedElementButton()
{
	if (UserCharacterData.UserSeq == -1)
		return;

	ULobbyMainUI* LobbyMainUI = Cast<ULobbyMainUI>(GetUIManager()->GetMainUI());
	if(IsValid(LobbyMainUI) == false)
		return;

	UCharacterListUI* CharacterList = LobbyMainUI->GetCharacterListUI();
	if(IsValid(CharacterList) == false)
		return;

	CharacterList->SetSelectedElement(this);
}

void UCharacterListElement::SetUserCharacterData(FUserCharacter Data)
{
	UserCharacterData = Data;
}

FUserCharacter UCharacterListElement::GetUserCharacterData()
{
	return UserCharacterData;
}
