// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/StatSet/StatSetMonster.h"
#include "RLRObjects/Characters/RLRMonster.h"
#include "RLR.h"

UStatSetMonster::UStatSetMonster()
{
}

void UStatSetMonster::UpdateTransForm(FVector NewTransform)
{
	SetMonsterTransform(NewTransform);

	if (ARLRMonster* monster = Cast<ARLRMonster>(GetOuter()))
	{
		AsyncTask(ENamedThreads::GameThread, [monster, NewTransform]()
			{
				monster->SetActorLocation(NewTransform);
			});
	}
}

void UStatSetMonster::UpdateHp(int32 NewHp)
{
	if (NewHp <= 0)
	{
		AsyncTask(ENamedThreads::GameThread, [this]()
		{
			OnOutOfHealth.Broadcast();
		});
	}
	else if (NewHp == GetMonsterMaxHp())
	{
		AsyncTask(ENamedThreads::GameThread, [this]()
		{
			OnRevive.Broadcast();
		});
	}

	SetMonsterHp(NewHp);
	OnHpChanged.Broadcast();
}