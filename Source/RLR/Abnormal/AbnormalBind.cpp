// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalBind.h"
#include "Player/PlayerCharacter.h"

UAbnormalBind::UAbnormalBind()
{
	PrimaryComponentTick.bCanEverTick = true;
	TimerDelegate.BindUFunction(this, FName("RemoveAbnormal"));
}

void UAbnormalBind::ApplyAbnormal(APlayerCharacter* Player, int duration)
{
	player = Player;
	player->SetMoveMode(MOVE_None);

	GetWorld()->GetTimerManager().SetTimer(Timer, TimerDelegate, duration, false);
}

void UAbnormalBind::RemoveAbnormal(APlayerCharacter* Player)
{
	player->SetMoveMode(MOVE_Walking);
	AActor* actor = GetOwner();
	actor->Destroy();
	
}
