// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Default/ActionMove.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "Player/RLRPlayerController.h"
#include "RLR.h"
#include "ActionSystem/ActionTask/ActionTask_MoveToLocation.h"
#include "NiagaraFunctionLibrary.h"

int UActionMove::SpawnCursorCnt = 1;

UActionMove::UActionMove():
	CursorPeriod(50)
{
	InstancingPolicy = EActionInstancingPolicy::InstancedPerActor;
	bIsCancelable = true;
}

bool UActionMove::PreActivateAction()
{
	bool bPossible = Super::PreActivateAction();
	if (!bPossible) return bPossible;

	if (!ASC) ASC = CurrentActorInfo->ActionSystemComponent.Get();
	if (!PlayerCharacter) PlayerCharacter = Cast<ARLRPlayerCharacter>(CurrentActorInfo->AvatarActor.Get());
	if (!Controller) Controller = PlayerCharacter->GetController<ARLRPlayerController>();

	ASC->GetActionData(TriggerTag, ActionData);

	if (ActionData.TriggerType == EInputTriggerType::TRIGGER_START)
	{
		ActionState = EActionState::STATE_INIT;
	}
	else if (ActionData.TriggerType == EInputTriggerType::TRIGGER_TRIGGER)
	{
		ActionState = EActionState::STATE_WAIT_ACTIVATE;
	}
	else if (ActionData.TriggerType == EInputTriggerType::TRIGGER_COMPLETE)
	{
		ActionState = EActionState::STATE_ACTIVATE;
	}

	return bPossible;
}

void UActionMove::ActivateAction()
{
	if (ActionState == EActionState::STATE_INIT)
	{
		StartMove();
	}
	else if (ActionState == EActionState::STATE_WAIT_ACTIVATE)
	{
		AddMovementInput();
	}
	else if (ActionState == EActionState::STATE_ACTIVATE)
	{
		//Cursor
		SpawnCursorCnt = 1;
		MoveToLocation();
	}
}

void UActionMove::CancelAction()
{
	Super::CancelAction();
}

void UActionMove::EndAction()
{
	Super::EndAction();
}

void UActionMove::StartMove()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Cursor, ActionData.MousePos, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);

	if (MoveTask)
	{
		MoveTask->ExternalCancel();
	}

	Controller->StopMovement();
}

void UActionMove::AddMovementInput()
{
	int tagCnt = ASC->GetGameplayTagCount(TriggerTag);
	if (tagCnt / CursorPeriod > SpawnCursorCnt)
	{
		SpawnCursorCnt++;
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Cursor, ActionData.MousePos, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FVector WorldDirection = (ActionData.MousePos - PlayerCharacter->GetActorLocation()).GetSafeNormal();
	PlayerCharacter->AddMovementInput(WorldDirection, 1.0f, false);
}

void UActionMove::MoveToLocation()
{
	MoveTask = UActionTask_MoveToLocation::CreateMoveTask(this, TEXT("Move"), PlayerCharacter, ActionData.MousePos);
	MoveTask->OnMoveFinish.AddDynamic(this, &UActionMove::OnMoveComplete);

	MoveTask->ReadyForActivation();
}

void UActionMove::OnMoveComplete(bool bSuccess)
{
	if (bSuccess) EndAction();
	else CancelAction();
}