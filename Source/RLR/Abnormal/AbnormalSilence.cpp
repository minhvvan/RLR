// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalSilence.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"


UAbnormalSilence::UAbnormalSilence()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalSilence::ApplyAbnormal(ARLRPlayerCharacter* other, int duration)
{
	if (other->IsA<ARLRPlayerCharacter>())
	{
		Player = other;
		Player->SetIsAttack(false);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalSilence::RemoveAbnormal, duration, false);
	}
}

void UAbnormalSilence::RemoveAbnormal()
{
	Player->SetIsAttack(true);
	AActor* actor = GetOwner();
	actor->Destroy();
}