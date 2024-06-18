// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalBind.h"
#include "Player/PlayerCharacter.h"
UAbnormalBind::UAbnormalBind()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UAbnormalBind::ApplyAbnormal(APlayerCharacter* Player)
{
	UE_LOG(LogTemp, Log, TEXT("Abnormal Bind Test"));
	//Player->SetIsMove(false);
	Player->SetOrientation();
}

void UAbnormalBind::RemoveAbnormal(APlayerCharacter* Player)
{
	//TODO : Set Timer and SetIsMove true
	Player->SetIsMove(true);
}

