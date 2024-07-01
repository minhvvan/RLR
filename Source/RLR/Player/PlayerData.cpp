// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerData.h"

APlayerData::APlayerData()
{
	SetData();
	
}

// TODO : Set DB Connection
void APlayerData::SetData()
{
	Status.AttackDamage = 1;
	Status.HpCurrent = 50;
	Status.HpMax = 50;
}