// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalProvoke.h"
#include "Player/PlayerCharacter.h"


UAbnormalProvoke::UAbnormalProvoke()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalProvoke::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalProvoke::RemoveAbnormal, duration, false);
	}
}

void UAbnormalProvoke::RemoveAbnormal()
{
	Player->BanInput(false);

	AActor* actor = GetOwner();
	actor->Destroy();
}