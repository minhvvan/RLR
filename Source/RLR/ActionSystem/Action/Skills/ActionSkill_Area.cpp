// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill_Area.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/RLRReticle.h"

UActionSkill_Area::UActionSkill_Area()
{
	InstancingPolicy = EActionInstancingPolicy::InstancedPerActor;
}

void UActionSkill_Area::CancelAction()
{
	Super::CancelAction();
}

void UActionSkill_Area::EndAction()
{
	ActionState = EActionState::STATE_END;
	Super::EndAction();

	//Actor당 Instancing되는 Action은 Init상태로 초기화
	if (InstancingPolicy == EActionInstancingPolicy::InstancedPerActor)
	{
		ActionState = EActionState::STATE_INIT;
	}
}

bool UActionSkill_Area::PreActivateAction()
{
	bool bPossible = Super::PreActivateAction();
	if (!bPossible) return bPossible;

	if (ActionState == EActionState::STATE_INIT)
	{
		ActionState = EActionState::STATE_WAIT_ACTIVATE;
	}
	else if (ActionState == EActionState::STATE_WAIT_ACTIVATE)
	{
		ActionState = EActionState::STATE_ACTIVATE;
	}

	return bPossible;
}

void UActionSkill_Area::ActivateAction()
{
	if (ActionState == EActionState::STATE_WAIT_ACTIVATE)
	{
		ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
		if (!Player) return;

		AUserController* Controller = Cast<AUserController>(Player->GetController());
		if (!Controller) return;

		//Spawn Reticle
		SpawnedReticle = GetWorld()->SpawnActor<ARLRReticle>(ReticleClass, Controller->GetClickPosition(), FRotator::ZeroRotator);
		SpawnedReticle->InitializeReticle(Controller);
	}
	else if (ActionState == EActionState::STATE_ACTIVATE)
	{
		//Play Anim & Activate Check ActionARLRReticle
		SpawnedReticle->Destroy();
		PlaySkillMontage();
	}
}

void UActionSkill_Area::OnCompletePlayMontage()
{
	EndAction();
}
