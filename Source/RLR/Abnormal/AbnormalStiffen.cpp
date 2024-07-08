// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalStiffen.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"


UAbnormalStiffen::UAbnormalStiffen()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalStiffen::ApplyAbnormal(ARLRPlayerCharacter* other, int duration)
{
	if (other->IsA<ARLRPlayerCharacter>())
	{
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalStiffen::RemoveAbnormal, duration, false);
	}
}

void UAbnormalStiffen::RemoveAbnormal()
{
	Player->BanInput(false);

	AActor* actor = GetOwner();
	actor->Destroy();
}