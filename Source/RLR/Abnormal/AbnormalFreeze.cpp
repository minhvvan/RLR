// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalFreeze.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"


UAbnormalFreeze::UAbnormalFreeze()
{
	PrimaryComponentTick.bCanEverTick = true;
	//slow = CreateDefaultSubobject<UAbnormalSlow>(TEXT("Slow"));
}

void UAbnormalFreeze::ApplyAbnormal(ARLRPlayerCharacter* other, int duration)
{
	if (other->IsA<ARLRPlayerCharacter>())
	{
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalFreeze::RemoveAbnormal, duration, false);
	}
}

void UAbnormalFreeze::RemoveAbnormal()
{
	Player->BanInput(false);
	slow->ApplyAbnormal(Player,1.f);

}
// 프리즈에서 조작 금지 -> 리무브 -> 슬로우 Apply -> Remove 형태로 구성.