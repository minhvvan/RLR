// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerData.generated.h"

/**
 *
 */
UCLASS()
class RLR_API APlayerData : public APlayerState
{
	GENERATED_BODY()

private:
	APlayerData();

	struct  Distribution
	{
		int HP;
		int MP;
		int Str;
		int Agility;
		int Inte;
	};
	struct Inherent
	{
		FString Name;
		int Level;
		int MainJob;
		int SubJob;
		float Exp;
		// TODO : Class = equip Title, Possess Title
		int AdventureLevel;
		int Talent;
		int ReputationValue;
		int NobleLevel;
	};

	//Default 로 변환.
	struct Status
	{
		int MpMax;
		int MpCurrent;
		float MpRecovery;

		int HpMax;
		int HpCurrent;
		float HpRecovery;

		int Defense;
		int AttackDamage;
		float AttackSpeed;
		float CoolTimeReduction;

		float MoveSpeed;
		float Avoid;
		float HpAbsorb;
		float CriticalDamage;
		float CriticalProbability;

		int Sheeld;
	};

	struct State
	{
		// TODO : 상태이상.
	};

	void SetData();

public:

	Distribution Distribution;
	Status Status;
	Inherent Inherent;
};
