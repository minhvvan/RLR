// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalBleeding.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"

//TODO : ���� ������ 
UAbnormalBleeding::UAbnormalBleeding()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalBleeding::ApplyAbnormal(ARLRPlayerCharacter* other, int duration)
{
	if (other->IsA<ARLRPlayerCharacter>())
	{
		Player = other;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalBleeding::RemoveAbnormal, duration, false);
	}
}

void UAbnormalBleeding::RemoveAbnormal()
{
	AActor* actor = GetOwner();
	actor->Destroy();
}