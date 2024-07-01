// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalElectric.h"
#include "Player/PlayerCharacter.h"

// TODO : ���� ������
UAbnormalElectric::UAbnormalElectric()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalElectric::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalElectric::RemoveAbnormal, duration, false);
	}
}

void UAbnormalElectric::RemoveAbnormal()
{
	AActor* actor = GetOwner();
	actor->Destroy();
}