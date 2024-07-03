// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/ActionTask/ActionTask.h"
#include "ActionSystem/ActionSystemComponent.h"

void UActionTask::OnDestroy(bool bInOwnerFinished)
{
	Action = nullptr;

	Super::OnDestroy(bInOwnerFinished);
}

void UActionTask::BeginDestroy()
{
	Super::BeginDestroy();
}

void UActionTask::SetActionSystemComponent(UActionSystemComponent* InASC)
{
	ActionSystemComponent = InASC;
}

void UActionTask::InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent)
{
	Super::InitSimulatedTask(InGameplayTasksComponent);
	SetActionSystemComponent(Cast<UActionSystemComponent>(TasksComponent.Get()));
}
