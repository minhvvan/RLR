// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/ActionDialogue.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "UI/DialogueUI.h"
#include "RLR.h"

UActionDialogue::UActionDialogue()
{
	InstancingPolicy = EActionInstancingPolicy::InstancedPerExecution;
}

bool UActionDialogue::PreActivateAction()
{
	bool bPosslbe = Super::PreActivateAction();
	return bPosslbe;
}

void UActionDialogue::ActivateAction()
{
	auto dialogueUI = GameInstance->GetUIManager()->OpenDialogue(DialogueUIClass);
	if (dialogueUI.Get())
	{
		dialogueUI->OnDialogueEnd.AddDynamic(this, &UActionDialogue::OnDialogueEnded);
	}
}

void UActionDialogue::CancelAction()
{
	Super::CancelAction();
}

void UActionDialogue::EndAction()
{
	Super::EndAction();
}

void UActionDialogue::OnDialogueEnded()
{
	//대화 종료 Callback
	EndAction();
}
