// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill.h"

void APlayerSkill::InitData()
{
	Data.Name = "Player";
	Data.Cind;
	Data.CollisionRange = FVector(2.f);
	Data.CoolTime = 5;
	Data.Cost;
	Data.Damage = 10;
	Data.Level;
}

void APlayerSkill::OnDestroty()
{
	if (bIsHit)
	{
		SetActorHiddenInGame(true);
		return;
	}
	Destroy();
}