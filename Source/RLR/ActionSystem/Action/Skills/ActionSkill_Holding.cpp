// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill_Holding.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/RLRReticle.h"
#include "UI/InGame/Skill/TimerProgressBar.h"
#include "GameManager/GameManager.h"
#include "GameManager/SkillManager.h"
#include "RLR.h"
#include <ActionSystem/AnimNotify_ActivateAction.h>
#include "Structs/SkillStructs.h"

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

	if (TimerWidget) TimerWidget->RemoveFromParent();
}
 
void UActionSkill_Holding::EndAction()
{
	if (TimerWidget) TimerWidget->RemoveFromParent();


	ActionState = EActionState::STATE_END;
	Super::EndAction();
}

bool UActionSkill_Holding::PreActivateAction()
{
	bool bPossible = Super::PreActivateAction();

	if (ActionState == EActionState::STATE_INIT)
	{
		// 스킬 상태 변경(INIT->ACTIVATE)
		ActionState = EActionState::STATE_ACTIVATE;
	}

	if (TimerWidget)
	{
		TimerWidget->SetTimerDuration(SkillData->Casting);
	}


	return bPossible;
}

void UActionSkill_Holding::ActivateAction()
{
	if (ActionState == EActionState::STATE_ACTIVATE)
	{
		//Play Montage
		PlaySkillMontage();
		
		ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
		if (!Player) return;

		if (TimerWidget)
		{
			if (TimerWidget->GetTimerDuration() <= 0)
			{
				/* 전체 시간을 4초로 설정 (로아 쏜살바람새 3초) */
				TimerWidget->SetTimerDuration(SkillData->Casting);
				timerStartTime = GetWorld()->GetTimeSeconds();
			}

			UAnimNotify_ActivateAction* AnimNotify = Cast<UAnimNotify_ActivateAction>(ActionMontage->Notifies[0].Notify);
			if (AnimNotify)
			{
				AnimNotify->OnTriggered.Clear();
				AnimNotify->OnTriggered.AddDynamic(this, &UActionSkill_Holding::OnAnimNotified);
			}

			// 두 번째 Notify (애니메이션 끝에서 타이머 제거) -> 현재는 필요없는 이벤트여서 주석처리 했습니다
			//UAnimNotify_ActivateAction* EndNotify = Cast<UAnimNotify_ActivateAction>(SkillAnim->Notifies[1].Notify);
			//if (EndNotify)
			//{
			//	EndNotify->OnTriggered.Clear();
			//	EndNotify->OnTriggered.AddDynamic(this, &UActionSkill_Holding::OnMontageEndNotified);
			//}
		}
		ActionState = EActionState::STATE_WAIT_CANCEL;
	}
	Super::ActivateAction();
}

void UActionSkill_Holding::OnCompletePlayMontage()
{
	
	if (ActionState != EActionState::STATE_WAIT_CANCEL)
	{
		EndAction();
	}
	else
	{
		/* 만약에 필요하다고 생각되면, 다시 반복 재생 가능 */
	}
}


void UActionSkill_Holding::OnAnimNotified()
{
	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	if (AnimInstance && ActionMontage)
	{
		float CurrentTime = GetWorld()->GetTimeSeconds();

		float ElapsedTime = CurrentTime - timerStartTime;
		
		if (TimerWidget->GetRemainingTime() > 1)
		{
			// HoldingLoop 섹션을 다시 반복
			AnimInstance->Montage_SetNextSection(FName("HoldingLoop"), FName("HoldingLoop"), ActionMontage);
		}
		else
		{
			// 남은 시간이 없으면 EndSection으로 이동
			AnimInstance->Montage_SetNextSection(FName("HoldingLoop"), FName("EndSection"), ActionMontage);
		}
	}
}

void UActionSkill_Holding::OnMontageEndNotified()
{
	if (TimerWidget) TimerWidget->RemoveFromParent();
}
