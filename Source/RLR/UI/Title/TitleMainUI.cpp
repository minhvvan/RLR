// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Title/TitleMainUI.h"
#include "UI/Title/ServerList.h"
#include "UI/Title/TitleRegisterUI.h"
#include "UI/Title/ServerListElement.h"

#include "Components/EditableTextBox.h"
#include "Components/Button.h"

#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"

#include "Structs/UtilStructs.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void UTitleMainUI::NativeConstruct()
{
	Super::NativeConstruct();

	ConnectServerButton->OnClicked.AddUniqueDynamic(this, &UTitleMainUI::OnClickedConnectServerButton);
	RegisterButton->OnClicked.AddUniqueDynamic(this, &UTitleMainUI::OnClickedRegisterButton);

	if (TitleRegisterUI)
	{
		TitleRegisterUI->OnRegisterCancelButtonClicked.AddUniqueDynamic(this, &UTitleMainUI::OnRegisterCancelButtonClicked);
		TitleRegisterUI->OnRegisterConfirmButtonClicked.AddUniqueDynamic(this, &UTitleMainUI::OnRegisterConfirmButtonClicked);
	}
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
	ChangeInputModeGameAndUI();
}

void UTitleMainUI::AddServerListElement(FServerData NewServerData)
{
	AsyncTask(ENamedThreads::GameThread, [this, NewServerData]()
		{
			ServerList->AddServerListElement(NewServerData);
		});
}

void UTitleMainUI::OnClickedConnectServerButton()
{
	/*
		서버에 로그인 패킷 보내기.
	*/

	FText ID = IDEditableTextBox->GetText();
	FText PW = PWEditableTextBox->GetText();
	UServerListElement* Element = ServerList->GetSelectedServer();

	if (IsValid(Element) == false)
	{
		GameInstance->GetNetworkManager()->SendLoginRequest(1, ID, PW);
		DEBUG_LOG("선택된 서버가 없습니다.");
		return;
	}

	/*
		뭐가 필요한지 몰라서 일단 ServerSeq만 담아서 보내봄..
	*/

	int32 ServerSeq = Element->GetServerData().ServerSeq;
	GameInstance->GetNetworkManager()->SendLoginRequest(ServerSeq, ID, PW);
}

void UTitleMainUI::OnClickedRegisterButton()
{
	if (TitleRegisterUI)
	{
		TitleRegisterUI->SetVisibility(ESlateVisibility::Visible);
	}
}

void UTitleMainUI::OnRegisterCancelButtonClicked()
{
	if (TitleRegisterUI)
	{
		TitleRegisterUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UTitleMainUI::OnRegisterConfirmButtonClicked()
{
	if (TitleRegisterUI)
	{
		/* 서버에 회원가입 완료 전달하기 */
		TitleRegisterUI->SetVisibility(ESlateVisibility::Hidden);
	}
}