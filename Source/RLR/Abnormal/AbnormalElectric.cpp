// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalElectric.h"
#include "Player/PlayerCharacter.h"


UAbnormalElectric::UAbnormalElectric()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalElectric::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalElectric::RemoveAbnormal, duration, false);
	}
}

void UAbnormalElectric::RemoveAbnormal()
{
	Player->BanInput(false);

	AActor* actor = GetOwner();
	actor->Destroy();
}