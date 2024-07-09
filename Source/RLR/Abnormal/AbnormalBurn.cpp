// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalBurn.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"

//TODO : 지속 데미지
UAbnormalBurn::UAbnormalBurn()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalBurn::ApplyAbnormal(ARLRPlayerCharacter* other, int duration)
{
	if (other->IsA<ARLRPlayerCharacter>())
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