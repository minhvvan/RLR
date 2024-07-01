// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalProvoke.h"
#include "Player/PlayerCharacter.h"


UAbnormalProvoke::UAbnormalProvoke()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalProvoke::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		//TODO : 스킬과 몬스터 구현 후 로직 구성.
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalProvoke::RemoveAbnormal, duration, false);
	}
}

void UAbnormalProvoke::RemoveAbnormal()
{
	Player->BanInput(false);

	AActor* actor = GetOwner();
	actor->Destroy();
}