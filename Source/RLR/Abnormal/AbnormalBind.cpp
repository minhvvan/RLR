// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalBind.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"

UAbnormalBind::UAbnormalBind()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalBind::ApplyAbnormal(ARLRPlayerCharacter* other, int duration)
{
	if (other->IsA<ARLRPlayerCharacter>())
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
