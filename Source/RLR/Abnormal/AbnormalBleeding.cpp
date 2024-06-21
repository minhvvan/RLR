// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalBleeding.h"
#include "Player/PlayerCharacter.h"


UAbnormalBleeding::UAbnormalBleeding()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalBleeding::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalBleeding::RemoveAbnormal, duration, false);
	}
}

void UAbnormalBleeding::RemoveAbnormal()
{
	Player->BanInput(false);

	AActor* actor = GetOwner();
	actor->Destroy();
}