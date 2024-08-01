// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DialogueUI.h"
#include "Components/Button.h"

void UDialogueUI::NativeConstruct()
{
	Super::NativeConstruct();

	BtnTest->OnClicked.AddDynamic(this, &UDialogueUI::OnDialogueEnded);
}

void UDialogueUI::OnDialogueEnded()
{
	OnDialogueEnd.Broadcast();
}
