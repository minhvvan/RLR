// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerSkill.generated.h"

UCLASS(abstract)
class RLR_API APlayerSkill : public AActor
{
	GENERATED_BODY()

private:

	struct FData
	{
		FString Name;
		// Image
		int Level;
		int Cost;
		int CoolTime;
		int Cind; // int -> enum or DB kind.
		int Damage;
		FVector CollisionRange;
	};
public:
	// TODO : UParticleSystem Change to Niagara System

	virtual void SkillAttack(FVector position, UParticleSystem* particle) PURE_VIRTUAL(APlayerSkill::SkillAttack, );

	virtual void Init() PURE_VIRTUAL(APlayerSkill::Init, );
	int GetDamage() { return Data.Damage; };

	
protected:
	void InitData();
	FData Data;
};
