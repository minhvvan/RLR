// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/ActionAttack.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "Player/PlayerCharacter.h"
#include "RLR.h"

UActionAttack::UActionAttack()
{
	InstancingPolicy = EActionInstancingPolicy::InstancedPerActor;
}

void UActionAttack::ActivateAction()
{
	RLR_LOG(LogRLR, Log, TEXT("Attack"));

	APlayerCharacter* Player = Cast<APlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	UActionTask_PlayMontage* AT = UActionTask_PlayMontage::CreatePlayMontageTask(this, TEXT("PlayAttackAnim"), Player->AttackMontage);
	AT->OnCompleted.AddDynamic(this, &UActionAttack::OnCompletePlayMontage);

	AT->ReadyForActivation();
}

void UActionAttack::CancelAction()
{
	Super::CancelAction();
}

void UActionAttack::EndAction()
{
	Super::EndAction();
}

void UActionAttack::OnCompletePlayMontage()
{
	EndAction();
}
