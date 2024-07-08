// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalStun.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"


UAbnormalStun::UAbnormalStun()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalStun::ApplyAbnormal(ARLRPlayerCharacter* other, int duration)
{
	if (other->IsA<ARLRPlayerCharacter>())
	{
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalStun::RemoveAbnormal, duration, false);
	}
}

void UAbnormalStun::RemoveAbnormal()
{
	Player->BanInput(false);

	AActor* actor = GetOwner();
	actor->Destroy();
}

