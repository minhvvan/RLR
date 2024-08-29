// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InGame/Quest/Dialogue/QuestDialogue.h"
#include "UI/DialogueUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UQuestDialogue::NativeConstruct()
{
	Super::NativeConstruct();

	BtnDeny->OnClicked.AddDynamic(this, &UQuestDialogue::OnQuestDialogueEnded);
	BtnAccept->OnClicked.AddDynamic(this, &UQuestDialogue::OnQuestAccepted);
}

void UQuestDialogue::OnQuestAccepted()
{
	// 수락했다는 것을 서버에 보내야 함
	OnQuestAccept.Broadcast();

}

void UQuestDialogue::OnQuestDialogueEnded()
{
	OnQuestDialogueEnd.Broadcast();
	this->RemoveFromViewport();
}

void UQuestDialogue::SetDialogueData(FString QuestDialogueString)
{
	//TODO : 나중에 FQuest->Needs에 따라 바뀌게 할 것
	TxtQuest->SetText(FText::FromString(QuestDialogueString));
}
