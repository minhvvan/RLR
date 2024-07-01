// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalPoison.h"
#include "Player/PlayerCharacter.h"

//TODO : ���� ������
UAbnormalPoison::UAbnormalPoison()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalPoison::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalPoison::RemoveAbnormal, duration, false);
	}
}

void UAbnormalPoison::RemoveAbnormal()
{
	AActor* actor = GetOwner();
	actor->Destroy();
}