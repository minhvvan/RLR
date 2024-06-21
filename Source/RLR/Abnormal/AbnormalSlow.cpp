// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalSlow.h"
#include "Player/PlayerCharacter.h"


UAbnormalSlow::UAbnormalSlow()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalSlow::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalSlow::RemoveAbnormal, duration, false);
	}
}

void UAbnormalSlow::RemoveAbnormal()
{
	Player->BanInput(false);

	AActor* actor = GetOwner();
	actor->Destroy();
}