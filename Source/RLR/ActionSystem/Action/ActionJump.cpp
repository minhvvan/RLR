// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/ActionJump.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "RLR.h"

UActionJump::UActionJump()
{
	InstancingPolicy = EActionInstancingPolicy::InstancedPerExecution;
}

void UActionJump::ActivateAction()
{
	RLR_LOG(LogRLR, Log, TEXT("Jump"));
	auto Avatar = GetAvatarActorFromActorInfo();
	//TODO: PlayMontageandWait AT 필요


	EndAction();
}

void UActionJump::CancelAction()
{
	Super::CancelAction();
}

void UActionJump::EndAction()
{
	Super::EndAction();
}
