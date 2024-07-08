// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/InGameMenu/InGameMenuTabListElement.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "InGameMenuTabListElement.h"



void UInGameMenuTabListElement::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	UInGameMenuTabListElement* ListElement = Cast<UInGameMenuTabListElement>(ListItemObject);

	InGameMenuUI = ListElement->InGameMenuUI;
	SetElementText(ListElement->ElementText);
	ButtonClickedFunc = ListElement->ButtonClickedFunc;
	ElementButton->OnClicked.AddUniqueDynamic(this, &UInGameMenuTabListElement::OnElementButtonClicked);
}

void UInGameMenuTabListElement::SetElementText(FText Text)
{
	ElementTextBlock->SetText(Text);
}

void UInGameMenuTabListElement::OnElementButtonClicked()
{
	if (ButtonClickedFunc)
	{
		if(InGameMenuUI)
			ButtonClickedFunc(InGameMenuUI);
	}
}
