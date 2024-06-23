// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalBurn.h"
#include "Player/PlayerCharacter.h"

//TODO : 지속 데미지
UAbnormalBurn::UAbnormalBurn()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalBurn::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalBurn::RemoveAbnormal, duration, false);
	}
}

void UAbnormalBurn::RemoveAbnormal()
{
	AActor* actor = GetOwner();
	actor->Destroy();
}