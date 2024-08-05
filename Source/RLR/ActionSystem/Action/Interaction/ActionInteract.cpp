// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Interaction/ActionInteract.h"

UActionInteract::UActionInteract()
{
}

bool UActionInteract::PreActivateAction()
{
	return Super::PreActivateAction();
}

void UActionInteract::ActivateAction()
{

}

void UActionInteract::CancelAction()
{
	Super::CancelAction();
}

void UActionInteract::EndAction()
{
	Super::EndAction();
}
