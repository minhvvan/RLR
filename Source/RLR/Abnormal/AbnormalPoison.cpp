// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalPoison.h"
#include "Player/PlayerCharacter.h"


UAbnormalPoison::UAbnormalPoison()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalPoison::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalPoison::RemoveAbnormal, duration, false);
	}
}

void UAbnormalPoison::RemoveAbnormal()
{
	Player->BanInput(false);

	AActor* actor = GetOwner();
	actor->Destroy();
}