// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Common/DialogueUI/DialogueDynamicButton.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"


void UDialogueDynamicButton::NativeConstruct()
{
	if (DynamicButton)
	{
		DynamicButton->OnClicked.AddDynamic(this, &UDialogueDynamicButton::OnButtonClicked);
	}
}

void UDialogueDynamicButton::SetButtonText(FString buttonText)
{
	ButtonText->SetText(FText::FromString(buttonText));
}

void UDialogueDynamicButton::SetButtonIndex(int32 index)
{
	buttonIdx = index;
}

void UDialogueDynamicButton::SetButtonType(int32 type)
{
	buttonType = type;
}

int32 UDialogueDynamicButton::GetButtonIndex()
{
	return buttonIdx;
}

int32 UDialogueDynamicButton::GetButtonType()
{
	return buttonType;
}

void UDialogueDynamicButton::OnButtonClicked()
{
	OnButtonClickedTwoParam.Broadcast(buttonType, buttonIdx);
}