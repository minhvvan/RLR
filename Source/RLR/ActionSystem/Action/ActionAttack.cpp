// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/ActionAttack.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "Player/RLRPlayerController.h"
#include "RLR.h"

UActionAttack::UActionAttack():
	RotationSpeed(1.f)
{
	InstancingPolicy = EActionInstancingPolicy::InstancedPerActor;
}

void UActionAttack::ActivateAction()
{
	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	ARLRPlayerController* Controller = Cast<ARLRPlayerController>(Player->GetController());
	if (!Controller) return;

	//Set Actor Orientation
	Controller->StopMovement();
	FVector MousePos = Controller->GetClickPosition();
	Player->SetTargetRotation(MousePos, RotationSpeed);

	UActionTask_PlayMontage* AT = UActionTask_PlayMontage::CreatePlayMontageTask(this, TEXT("PlayAttackAnim"), Player->AttackMontage);
	AT->OnCompleted.AddDynamic(this, &UActionAttack::OnCompletePlayMontage);

	AT->ReadyForActivation();
	
	Super::ActivateAction();
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
