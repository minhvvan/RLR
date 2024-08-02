// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DialogueUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UDialogueUI::NativeConstruct()
{
	Super::NativeConstruct();

	BtnTest->OnClicked.AddDynamic(this, &UDialogueUI::OnDialogueEnded);
}

void UDialogueUI::SetDialogueData(FString DialogueString)
{
	//TODO: 대화 UI가 어떻게 될지에 따라 변경해야 함
	TxtTest->SetText(FText::FromString(DialogueString));
}

void UDialogueUI::OnDialogueEnded()
{
	OnDialogueEnd.Broadcast();
}
