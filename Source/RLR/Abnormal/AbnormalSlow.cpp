// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalSlow.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"


UAbnormalSlow::UAbnormalSlow()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalSlow::ApplyAbnormal(ARLRPlayerCharacter* other, int duration)
{
	if (other->IsA<ARLRPlayerCharacter>())
	{
		UE_LOG(LogTemp, Log, TEXT("asd"));
	}
}

void UAbnormalSlow::RemoveAbnormal()
{
	Player->BanInput(false);

	AActor* actor = GetOwner();
	actor->Destroy();
}