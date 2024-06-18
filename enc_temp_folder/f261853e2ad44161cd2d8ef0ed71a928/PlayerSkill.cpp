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

void APlayerSkill::SetAbnormal(UClass* AbnormalClass, UAbnormal*& abnormal)
{
	//Abnormal = CreateDefaultSubobject<UAbnormalBind>(TEXT("Abnormal"));
	if (AbnormalClass && AbnormalClass->IsChildOf(UAbnormal::StaticClass()))
	{
		abnormal = NewObject<UAbnormal>(this, AbnormalClass, TEXT("Abnormal"));
		abnormal->RegisterComponent();
	}

}
