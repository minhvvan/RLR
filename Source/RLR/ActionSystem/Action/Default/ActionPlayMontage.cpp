// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Default/ActionPlayMontage.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "Player/RLRPlayerController.h"
#include "GameManager/LiteralManager.h"

UActionPlayMontage::UActionPlayMontage()
{
	InstancingPolicy = EActionInstancingPolicy::InstancedPerActor;
}

bool UActionPlayMontage::PreActivateAction()
{
	bool bPossible = Super::PreActivateAction();

	return bPossible;
}

void UActionPlayMontage::ActivateAction()
{
	Super::ActivateAction();
	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	auto* Controller = Player->GetController();
	if (!Controller) return;

	Controller->StopMovement();

	UActionTask_PlayMontage* AT = UActionTask_PlayMontage::CreatePlayMontageTask(this, RLRLITERAL.ActionPlayMontage_PlayAnim, ActionMontage);
	AT->OnCompleted.AddDynamic(this, &UActionPlayMontage::OnCompletePlayMontage);

	AT->ReadyForActivation();
}

void UActionPlayMontage::CancelAction()
{
	Super::CancelAction();
}

void UActionPlayMontage::EndAction()
{
	Super::EndAction();
}