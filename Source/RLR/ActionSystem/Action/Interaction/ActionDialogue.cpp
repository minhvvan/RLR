// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Interaction/ActionDialogue.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/GameplayTagManager.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "UI/DialogueUI.h"
#include "RLR.h"

UActionDialogue::UActionDialogue()
{
	InstancingPolicy = EActionInstancingPolicy::InstancedPerExecution;
	bIsCancelable = true;
}

bool UActionDialogue::PreActivateAction()
{
	bool bPosslbe = Super::PreActivateAction();
	return bPosslbe;
}

void UActionDialogue::ActivateAction()
{
	UActionSystemComponent* playerASC = CurrentActorInfo->ActionSystemComponent.Get();
	if (!playerASC) return;

	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	FActionData actionData;
	playerASC->GetActionData(TagManager.Action_Interaction_Dialogue, actionData);

	auto dialogueUI = GameInstance->GetUIManager()->OpenDialogue(actionData.UIClass);
	if (dialogueUI.Get())
	{
		dialogueUI->OnDialogueEnd.AddDynamic(this, &UActionDialogue::OnDialogueEnded);
		dialogueUI->SetDialogueData(actionData.InteractionData.DialogueString);
		dialogueUI->SetNPCData(actionData.InteractionData.NPCSeq, actionData.InteractionData.QuestSeq);
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
