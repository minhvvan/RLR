// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill_Holding.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "UI/InGame/Skill/TimerProgressBar.h"
#include "GameManager/GameManager.h"
#include "GameManager/SkillManager.h"
#include "RLR.h"

UActionSkill_Holding::UActionSkill_Holding()
{
	InstancingPolicy = EActionInstancingPolicy::InstancedPerActor;
	bIsCancelable = true;
}

void UActionSkill_Holding::CancelAction()
{
	if (ActionState != EActionState::STATE_WAIT_CANCEL) return;
	//Stop Montage
	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	UActionSystemComponent* ASC = Player->GetActionSystemComponent();
	if (!ASC) return;
	
	ASC->CurrentMontageStop();

	Super::CancelAction();
}
 
void UActionSkill_Holding::EndAction()
{
	if (TimerWidget) TimerWidget->RemoveFromParent();

	Super::EndAction();
}

bool UActionSkill_Holding::PreActivateAction()
{
	bool bPossible = Super::PreActivateAction();

	if (ActionState == EActionState::STATE_INIT)
	{
		//스킬 상태 변경(INIT->ACTIVATE)
		ActionState = EActionState::STATE_ACTIVATE;
	}

	if (TimerWidget)
	{
		TimerWidget->SetTimerDuration(SkillData->Duration);
	}

	return bPossible;
}

void UActionSkill_Holding::ActivateAction()
{
	Super::ActivateAction();

	//Play Montage
	PlaySkillMontage();

	//Set Action State
	ActionState = EActionState::STATE_WAIT_CANCEL;
}

void UActionSkill_Holding::OnCompletePlayMontage()
{
	EndAction();
}