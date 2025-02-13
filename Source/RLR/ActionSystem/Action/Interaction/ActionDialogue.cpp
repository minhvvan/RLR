// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Interaction/ActionDialogue.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/PostalManager.h"
#include "GameManager/GameplayTagManager.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "Player/RLRPlayerController.h"
#include "UI/DialogueUI.h"
#include "UI/InGame/Post/PostOverlayUI.h"
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

	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	AController* Controller = Player->GetController();
	if (Controller)
	{
		Controller->StopMovement();

		ARLRPlayerController* PlayerController = Cast<ARLRPlayerController>(Controller);
		if (PlayerController)
		{
			PlayerController->StopOtherAction(RLRTAG.Action_Default_Move);
		}
	}

	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	FActionData actionData;
	playerASC->GetActionData(TagManager.Action_Interaction_Dialogue, actionData);

	auto dialogueUI = GameInstance->GetUIManager()->OpenPage<UDialogueUI>(RLRTAG.Page_Dialogue, actionData.UIClass);
	if (dialogueUI.Get())
	{
		dialogueUI->OnDialogueEnd.Clear();
		dialogueUI->OnDialogueEnd.AddDynamic(this, &UActionDialogue::OnDialogueEnded);
		dialogueUI->SetDialogueData(actionData.InteractionData.DialogueString);
		dialogueUI->SetNPCNameData(actionData.InteractionData.NPCName);
		dialogueUI->SetNPCData(actionData.InteractionData.NPCSeq);
		dialogueUI->UpdateNPCFunctionality();
	}

	UPostOverlayUI* PostUI = GameInstance->GetUIManager()->GetSubUI<UPostOverlayUI>(RLRTAG.UI_Post);
	if (PostUI)
	{
		PostUI->OnPostUIEnd.Clear();
		PostUI->OnPostUIEnd.AddDynamic(this, &UActionDialogue::OnDialogueEnded);
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
	UPostOverlayUI* PostUI = GameInstance->GetUIManager()->GetSubUI<UPostOverlayUI>(RLRTAG.UI_Post);
	if (PostUI->GetWritingPostStatus())
	{
		PostUI->ManageWritingPost();
	}
	else
	{
		PostUI->SetButtonsEnable();
		GameInstance->GetUIManager()->ClosePage();
		EndAction();
	}
	
	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	AController* Controller = Player->GetController();
	if (Controller)
	{
		ARLRPlayerController* PlayerController = Cast<ARLRPlayerController>(Controller);
		if (PlayerController)
		{
			PlayerController->RecoverOtherAction(RLRTAG.Action_Default_Move);
		}
	}
}
