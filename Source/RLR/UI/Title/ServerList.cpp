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
	SetUIType(EUIType::SERVER_LIST);
	
}

void UServerList::Init()
{
	Super::Init();
	ServerListScrollBox->ClearChildren();
	Clear();

	TSubclassOf<UServerListElement> ElementClass = GetWidgetClass<UServerListElement>("WBP_ServerListElement");
	if (IsValid(ElementClass) == false)
	{
		DEBUG_MESSAGE;
		return;
	}

	for(int32 i = 0 ; i < ServerListMaxCount; i++)
	{
		UServerListElement* NewServerListElement = CreateWidget<UServerListElement>(this, ElementClass);
		NewServerListElement->SetParent(this);
		NewServerListElement->SetVisibility(ESlateVisibility::Hidden);
		ServerListElementMap.Add(i, NewServerListElement);
		ServerListScrollBox->AddChild(NewServerListElement);
	}

}

void UServerList::RefreshUI()
{
	Super::RefreshUI();

}

void UServerList::Clear()
{
	Super::Clear();

	for (TTuple<int32, UServerListElement*> Iter : ServerListElementMap)
	{
		int32 ServerSeq = Iter.Key;
		UServerListElement* Element = Iter.Value;
		Element->Clear();
	}
}

void UServerList::AddServerListElement(FServerData NewServerData)
{

	
	int32 ServerSeq = NewServerData.ServerSeq;

	if (ServerListElementMap.Contains(ServerSeq) == false)
	{
		//ServerListMaxCount 값보다 높은 ServerSeq 값이 들어왔으니, ServerListMaxCount 수정.
		DEBUG_MESSAGE;
		return;
	}

	UServerListElement* Element = ServerListElementMap[ServerSeq];
	Element->SetServerData(NewServerData);
}

void UServerList::SetSelectedServer(UServerListElement* Element)
{
	if(IsValid(Element) == false)
		return;
	if(IsValid(SelectedElement) == true)
		SelectedElement->UnHighlight();

	SelectedElement = Element;
	SelectedElement->Highlight();
}

UServerListElement* UServerList::GetSelectedServer()
{
	if(IsValid(SelectedElement) == false)
		return nullptr;

	return SelectedElement;
}
