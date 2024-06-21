// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalBind.h"
#include "Player/PlayerCharacter.h"

UAbnormalBind::UAbnormalBind()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalBind::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		Player->SetMoveMode(MOVE_None);

		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalBind::RemoveAbnormal, duration, false);
	}
}

void UAbnormalBind::RemoveAbnormal()
{
	Player->SetMoveMode(MOVE_Walking);

	AActor* actor = GetOwner();
	actor->Destroy();
}
