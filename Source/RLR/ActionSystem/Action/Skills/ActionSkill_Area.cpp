// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill_Area.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/RLRReticle.h"
#include "GameManager/GameManager.h"
#include "GameManager/SkillManager.h"
#include "UI/InGame/Skill/SkillProgressBar.h"
#include "ActionSystem/AnimNotify_ActivateAction.h"
#include "RLR.h"

UActionSkill_Area::UActionSkill_Area()
{
	InstancingPolicy = EActionInstancingPolicy::InstancedPerActor;
}

void UActionSkill_Area::CancelAction()
{
	//Remove Reticle
	if (SpawnedReticle)
	{
		SpawnedReticle->Destroy();
	}

	Super::CancelAction();
}

void UActionSkill_Area::EndAction()
{
	ActionState = EActionState::STATE_END;
	Super::EndAction();
}

bool UActionSkill_Area::PreActivateAction()
{
	bool bPossible = false;
	if (!SkillData) SetSkillData();

	if (ActionState == EActionState::STATE_INIT)
	{
		if (CheckBlockTag()) return false;
		bPossible = true;

		bIsActive = true;
		bIsAbilityEnding = false;

		ActionState = EActionState::STATE_WAIT_ACTIVATE;
	}
	else if (ActionState == EActionState::STATE_WAIT_ACTIVATE)
	{
		bPossible = Super::PreActivateAction();
		ActionState = EActionState::STATE_ACTIVATE;
		bIsCancelable = false;
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

		if (!SkillData) SetSkillData();

		//Spawn Reticle
		SpawnedReticle = GetWorld()->SpawnActorDeferred<ARLRReticle>(ReticleClass, FTransform::Identity);
		SpawnedReticle->InitializeReticle(Controller, SkillData->CollisionRange.X);

		FTransform SpawnLoc(Controller->GetClickPosition());
		SpawnedReticle->FinishSpawning(SpawnLoc);
	}
	else if (ActionState == EActionState::STATE_ACTIVATE)
	{
		//Play Anim & Activate Check ActionARLRReticle
		SpawnedReticle->Destroy();
		PlaySkillMontage();

		if (TimerWidget)
		{
			//Notify가 하나일 때 가능 늘어나면 변경 필요
			TimerWidget->SetSkillDuration(SkillAnim->Notifies[0].GetTriggerTime());
			UAnimNotify_ActivateAction* AnimNotify = Cast<UAnimNotify_ActivateAction>(SkillAnim->Notifies[0].Notify);
			if (AnimNotify)
			{
				AnimNotify->OnTriggered.Clear();
				AnimNotify->OnTriggered.AddDynamic(this, &UActionSkill_Area::OnAnimNotified);
			}
		}

		Super::ActivateAction();
	}
}

void UActionSkill_Area::OnCompletePlayMontage()
{
	bIsCancelable = true;
	EndAction();
}

void UActionSkill_Area::OnAnimNotified()
{
	if (TimerWidget) TimerWidget->RemoveFromParent();
}
