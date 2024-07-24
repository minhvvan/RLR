// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/StatSet/StatSetMonster.h"
#include "RLR.h"
#include "RLRObjects/Characters/RLRMonster.h"

void UStatSetMonster::UpdateTransForm(FVector NewTransform)
{
	SetMonsterTransform(NewTransform);

	if (ARLRMonster* monster = Cast<ARLRMonster>(GetOuter()))
	{
		RLR_LOG(LogRLR, Log, TEXT("%s"), *monster->GetName());
		monster->SetActorLocation(NewTransform);
	}
}

void UStatSetMonster::UpdateHp(int32 NewHp)
{
	RLR_LOG(LogRLR, Log, TEXT("Before: %d"), GetMonsterHp());
	SetMonsterHp(NewHp);
	RLR_LOG(LogRLR, Log, TEXT("After: %d"), GetMonsterHp());
}