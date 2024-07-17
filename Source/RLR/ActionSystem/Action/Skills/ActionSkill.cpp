// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"

UActionSkill::UActionSkill():
	RotationSpeed(10.f)
{
	ActionState = EActionState::STATE_INIT;
}

void UActionSkill::PlaySkillMontage()
{
	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	AUserController* Controller = Cast<AUserController>(Player->GetController());
	if (!Controller) return;

	UActionSystemComponent* ASC = Player->GetActionSystemComponent();
	if (!ASC) return;

	//Set Actor Orientation
	Controller->StopMovement();
	FVector MousePos = Controller->GetClickPosition();
	Player->SetTargetRotation(MousePos, RotationSpeed);

	FActionData Data;
	Data.MousePos = MousePos;
	ASC->AddActionData(FollowTriggerTag, Data);

	//Play Montage
	UActionTask_PlayMontage* AT = UActionTask_PlayMontage::CreatePlayMontageTask(this, TEXT("PlaySkillAnim"), SkillAnim);
	AT->OnCompleted.AddDynamic(this, &ThisClass::OnCompletePlayMontage);

	AT->ReadyForActivation();
}

void UActionSkill::OnCompletePlayMontage()
{
	EndAction();
}