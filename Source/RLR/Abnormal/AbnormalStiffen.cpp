// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalStiffen.h"
#include "Player/PlayerCharacter.h"


UAbnormalStiffen::UAbnormalStiffen()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalStiffen::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
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