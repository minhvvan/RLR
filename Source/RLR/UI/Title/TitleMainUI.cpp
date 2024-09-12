// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Title/TitleMainUI.h"
#include "UI/Title/ServerList.h"
#include "UI/Title/ServerListElement.h"

#include "Components/EditableTextBox.h"
#include "Components/Button.h"

#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void UTitleMainUI::NativeConstruct()
{
	Super::NativeConstruct();


	ConnectServerButton->OnClicked.AddUniqueDynamic(this, &UTitleMainUI::OnClickedConnectServerButton);
}

void UTitleMainUI::RefreshUI()
{
	Super::RefreshUI();
	ServerList->Clear();
	GameInstance->GetNetworkManager()->SendServerListRequest();
}

void UTitleMainUI::Clear()
{
	Super::Clear();
}

void UTitleMainUI::SetInputMode()
{
	ChangeInputModeUIOnly();
}

void UTitleMainUI::AddServerListElement(FServerData NewServerData)
{
	ServerList->AddServerListElement(NewServerData);
}

void UTitleMainUI::OnClickedConnectServerButton()
{
	/*
		서버에 로그인 패킷 보내기.
	*/

	FText ID = IDEditableTextBox->GetText();
	FText PW = PWEditableTextBox->GetText();
	//UServerListElement* Element = ServerList->GetSelectedServer();

	/*if (IsValid(Element) == false)
	{
		DEBUG_LOG("선택된 서버가 없습니다.");
		return;
	}*/

	//FServerData Data = Element->GetServerData();

	/*
		뭐가 필요한지 몰라서 일단 ServerSeq만 담아서 보내봄..
	*/

	GameInstance->GetNetworkManager()->SendLoginRequest(1, ID, PW);
}
