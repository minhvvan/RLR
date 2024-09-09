// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Title/ServerList.h"
#include "UI/Title/ServerListElement.h"
#include "UI/Title/TitleMainUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"

#include "Components/ScrollBox.h"


void UServerList::NativeConstruct()
{
	Super::NativeConstruct();
	Clear();
}

void UServerList::RefreshUI()
{
	Super::RefreshUI();

}

void UServerList::Clear()
{
	Super::Clear();

	ServerListElementMap.Empty();
	ServerListScrollBox->ClearChildren();

}

void UServerList::AddServerListElement(FServerData NewServerData)
{
	if (ServerListElementMap.Contains(NewServerData.ServerSeq) == true)
		return;

	UServerListElement* NewServerListElement = CreateWidget<UServerListElement>(this,GetWidgetClass<UServerListElement>("WBP_ServerListElement"));
	if(IsValid(NewServerListElement) == false)
		return;

	NewServerListElement->SetServerData(NewServerData);
	NewServerListElement->SetParent(this);
	ServerListElementMap.Add(NewServerData.ServerSeq, NewServerListElement);
}

void UServerList::SetSelectedServer(UServerListElement* Element)
{
	if(IsValid(Element) == false)
		return;

	SelectedElement = Element;
}

UServerListElement* UServerList::GetSelectedServer()
{
	if(IsValid(SelectedElement) == false)
		return nullptr;

	return SelectedElement;
}
