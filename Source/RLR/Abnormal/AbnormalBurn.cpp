// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalBurn.h"
#include "Player/PlayerCharacter.h"


UAbnormalBurn::UAbnormalBurn()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalBurn::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalBurn::RemoveAbnormal, duration, false);
	}
}

void UAbnormalBurn::RemoveAbnormal()
{
	Player->BanInput(false);

	AActor* actor = GetOwner();
	actor->Destroy();
}