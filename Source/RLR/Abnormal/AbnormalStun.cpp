// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalStun.h"

UAbnormalStun::UAbnormalStun()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UAbnormalStun::ApplyAbnormal(APlayerCharacter* Player)
{
	UE_LOG(LogTemp, Log, TEXT("Abnormal Stun Test"));
}

void UAbnormalStun::RemoveAbnormal(APlayerCharacter* Player)
{

}

