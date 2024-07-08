// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalElectric.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"

// TODO : ���� ������
UAbnormalElectric::UAbnormalElectric()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalElectric::ApplyAbnormal(ARLRPlayerCharacter* other, int duration)
{
	if (other->IsA<ARLRPlayerCharacter>())
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalElectric::RemoveAbnormal, duration, false);
	}
}

void UAbnormalElectric::RemoveAbnormal()
{
	AActor* actor = GetOwner();
	actor->Destroy();
}