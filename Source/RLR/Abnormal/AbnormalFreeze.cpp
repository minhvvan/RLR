// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalFreeze.h"
#include "Player/PlayerCharacter.h"


UAbnormalFreeze::UAbnormalFreeze()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalFreeze::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalFreeze::RemoveAbnormal, duration, false);
	}
}

void UAbnormalFreeze::RemoveAbnormal()
{
	Player->BanInput(false);

	AActor* actor = GetOwner();
	actor->Destroy();
}