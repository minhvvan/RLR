// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalPoison.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"

//TODO : ���� ������
UAbnormalPoison::UAbnormalPoison()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalPoison::ApplyAbnormal(ARLRPlayerCharacter* other, int duration)
{
	if (other->IsA<ARLRPlayerCharacter>())
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalPoison::RemoveAbnormal, duration, false);
	}
}

void UAbnormalPoison::RemoveAbnormal()
{
	AActor* actor = GetOwner();
	actor->Destroy();
}