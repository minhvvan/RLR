// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Title/ServerListElement.h"
#include "UI/Title/ServerList.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"


void UServerListElement::NativeConstruct()
{
	Super::NativeConstruct();
	
	ServerSelectButton->OnClicked.AddUniqueDynamic(this, &UServerListElement::OnClickedServerSelectButton);
}

void UServerListElement::RefreshUI()
{
	Super::RefreshUI();

	if (ServerData.ServerSeq == -1)
	{
		Clear();
		return;
	}

	SetVisibility(ESlateVisibility::Visible);

	FText ServerName = FText::FromString(ServerData.ServerName);
	ServerNameText->SetText(ServerName);
}

void UServerListElement::Clear()
{
	Super::Clear();
	ServerData.ServerSeq = -1;
	SetVisibility(ESlateVisibility::Hidden);
}

void UServerListElement::SetServerData(FServerData NewServerData)
{
	ServerData = NewServerData;
	RefreshUI();
}

FServerData UServerListElement::GetServerData()
{
	return ServerData;
}

void UServerListElement::OnClickedServerSelectButton()
{
	if(IsValid(Parent) == false)
		return;
	
	UServerList* ServerList = Cast<UServerList>(GetParent());
	if(IsValid(ServerList) == false)
		return;

	ServerList->SetSelectedServer(this);
}

