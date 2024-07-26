// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/StatSet/StatSetPlayer.h"

void UStatSetPlayer::UpdateStat()
{
	UpdateLevel(GetLevel());
	UpdateExp(GetExp());
	UpdateTotalStatus(GetTotalStatus());
	UpdateSetStatus(GetSetStatus());
}

void UStatSetPlayer::UpdateLevel(int32 NewLevel)
{
	SetLevel(NewLevel);
	OnChangedLevel.Broadcast();
}

void UStatSetPlayer::UpdateExp(int32 NewExp)
{
	SetExp(NewExp);
	OnChangedExp.Broadcast();
}

void UStatSetPlayer::UpdateTotalStatus(FTotalStatus NewTotalStatus)
{
	SetTotalStatus(NewTotalStatus);
	OnChangedTotalStatus.Broadcast();
}

void UStatSetPlayer::UpdateSetStatus(FSetStatus NewSetStatus)
{
	SetSetStatus(NewSetStatus);
	OnChangedSetStatus.Broadcast();
}
