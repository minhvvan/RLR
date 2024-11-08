// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Interaction/ActionInteract.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "Player/RLRPlayerController.h"
#include "UI/InGame/Skill/TimerProgressBar.h"
#include "RLR.h"

UActionInteract::UActionInteract()
{
	InstancingPolicy = EActionInstancingPolicy::InstancedPerExecution;
	bIsCancelable = true;
}

bool UActionInteract::PreActivateAction()
{
	bool bPossible = Super::PreActivateAction();
	if (!bPossible) return bPossible;
	else ActionState = EActionState::STATE_ACTIVATE;

	//Attach UI
	if (!InteractTimerUI)
	{
		//USkillProgressBar 재사용 가능 -> 이름 변경 필요(UTimerProgressBar)
		InteractTimerUI = CreateWidget<UTimerProgressBar>(GetWorld(), InteractTimerClass);
	}

	return bPossible;
}

void UActionInteract::ActivateAction()
{
	RLR_LOG(LogRLR, Log, TEXT("Interaction"));
	PlayActionMontage();

	if (InteractTimerUI)
	{
		//Test
		InteractTimerUI->SetTimerDuration(2.f);
		InteractTimerUI->AddToViewport();
	}
}

void UActionInteract::CancelAction()
{
	RLR_LOG(LogRLR, Log, TEXT("Cancel"));
	Super::CancelAction();
}

void UActionInteract::EndAction()
{
	if (InteractTimerUI) InteractTimerUI->RemoveFromParent();

	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	ARLRPlayerController* Controller = Cast<ARLRPlayerController>(Player->GetController());
	if (!Controller) return;

	UActionSystemComponent* ASC = Player->GetActionSystemComponent();
	if (!ASC) return;

	ASC->CurrentMontageStop();

	Super::EndAction();
}

void UActionInteract::PlayActionMontage()
{
	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	ARLRPlayerController* Controller = Cast<ARLRPlayerController>(Player->GetController());
	if (!Controller) return;

	UActionSystemComponent* ASC = Player->GetActionSystemComponent();
	if (!ASC) return;

	//Set Actor Orientation
	Controller->StopMovement();
	//Player->SetTargetRotation(MousePos, RotationSpeed);

	//Play Montage
	//TODO: StartTime = MontageLength - InteractionTime
	float montageLength = InteractAnim->GetPlayLength();
	float startTime = montageLength - 2.f;

	UActionTask_PlayMontage* AT = UActionTask_PlayMontage::CreatePlayMontageTask(this, TEXT("PlayInteractAnim"), InteractAnim, 1.f, NAME_None, true, 1.f, startTime);
	AT->OnCompleted.AddDynamic(this, &ThisClass::OnCompletePlayMontage);
	AT->OnCancelled.AddDynamic(this, &ThisClass::OnCompletePlayMontage);

	AT->ReadyForActivation();
}

void UActionInteract::OnCompletePlayMontage()
{
	//TODO: Request Reward
	if (InteractTimerUI) InteractTimerUI->RemoveFromParent();
	EndAction();
}