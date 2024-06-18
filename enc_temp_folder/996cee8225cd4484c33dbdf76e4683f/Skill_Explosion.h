// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include <Kismet/GameplayStatics.h>
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PlayerSkill.h"
#include "Skill_Explosion.generated.h"


UCLASS()
class RLR_API ASkill_Explosion : public APlayerSkill
{
	GENERATED_BODY()
	
public:	
	ASkill_Explosion();

	virtual void Tick(float DeltaTime) override;

	USphereComponent* Collision;
	UPROPERTY(EditAnywhere, Category = Effect);
	UParticleSystem* Attack;
	UParticleSystem* GetAttackParticle() { return Attack; }
	virtual void EndPlay(const EEndPlayReason::Type);
	virtual void SkillAttack(FVector, UParticleSystem*) override;
	virtual void Init() override;
private:
	float spawnTime;
};
