// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalSilence.h"
#include "Player/PlayerCharacter.h"


UAbnormalSilence::UAbnormalSilence()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalSilence::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalSilence::RemoveAbnormal, duration, false);
	}
}

void UAbnormalSilence::RemoveAbnormal()
{
	Player->BanInput(false);

	AActor* actor = GetOwner();
	actor->Destroy();
}