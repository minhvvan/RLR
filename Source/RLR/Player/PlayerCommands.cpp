// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCommands.h"

APlayerCommands::APlayerCommands()
{
	PrimaryActorTick.bCanEverTick = true;
}


void APlayerCommands::Init()
{
	// TODO : 모든 스킬 커맨드 적용할 방식 찾아 적용하기.
	ConstructorHelpers::FObjectFinder<UInputAction>container(TEXT("/Game/Player/Input/Action_SkillQ"));
	if (container.Succeeded())
	{
		Skill.Q = container.Object;
	}
}

void APlayerCommands::TestLog()
{
	UE_LOG(LogTemp, Log, TEXT("Test Log Command Key : Q"));
}
