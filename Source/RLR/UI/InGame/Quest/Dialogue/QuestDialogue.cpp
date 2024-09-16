// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InGame/Quest/Dialogue/QuestDialogue.h"
#include "UI/DialogueUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "Structs/UtilStructs.h"

void UQuestDialogue::NativeConstruct()
{
	Super::NativeConstruct();
	SetUIType(EUIType::QUEST_DIALOGUE);

	BtnDeny->OnClicked.AddDynamic(this, &UQuestDialogue::OnQuestDialogueEnded);
	BtnAccept->OnClicked.AddDynamic(this, &UQuestDialogue::OnQuestAccepted);
}

void UQuestDialogue::OnQuestAccepted()
{
	/* TODO : NPCSeq와 NPC별 Quest 정보를 어디서 가져와야할지 몰라서 임시값으로 고정해둠 */
	OnQuestAccept.Broadcast();
	GameInstance->GetNetworkManager()->SendQuestAddPacket(CurrentNPCSeq, CurrentQuestSeq);
	
	this->RemoveFromViewport();
}

void UQuestDialogue::OnQuestDialogueEnded()
{
	OnQuestDialogueEnd.Broadcast();
	this->RemoveFromViewport();
}

void UQuestDialogue::SetDialogueData(FString QuestDialogueString, int32 NPCSeq, int32 QuestSeq)
{
	//TODO : 나중에 FQuest->Needs에 따라 바뀌게 할 것
	TxtQuest->SetText(FText::FromString(QuestDialogueString));
	CurrentNPCSeq = NPCSeq;
	CurrentQuestSeq = QuestSeq;
}
