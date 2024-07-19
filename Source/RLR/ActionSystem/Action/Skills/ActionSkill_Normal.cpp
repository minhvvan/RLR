// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill_Normal.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "RLR.h"

UActionSkill_Normal::UActionSkill_Normal()
{
}

void UActionSkill_Normal::CancelAction()
{
	Super::CancelAction();
}

void UActionSkill_Normal::EndAction()
{
	ActionState = EActionState::STATE_END;
	Super::EndAction();

	//Actor당 Instancing되는 Action은 Init상태로 초기화
	if (InstancingPolicy == EActionInstancingPolicy::InstancedPerActor)
	{
		ActionState = EActionState::STATE_INIT;
	}
}

bool UActionSkill_Normal::PreActivateAction()
{
	bool bPossible = Super::PreActivateAction();
	if (ActionState != EActionState::STATE_INIT) bPossible = false;

	//스킬 상태 변경(INIT->ACTIVATE)
	if (bPossible) ActionState = EActionState::STATE_ACTIVATE;

	return bPossible;
}

void UActionSkill_Normal::ActivateAction()
{
	Super::ActivateAction();
	PlaySkillMontage();
}

void UActionSkill_Normal::OnCompletePlayMontage()
{
	EndAction();
}
