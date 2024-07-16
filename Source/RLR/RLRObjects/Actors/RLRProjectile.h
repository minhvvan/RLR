// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLRObjects/Actors/RLRActor.h"
#include "RLRProjectile.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API ARLRProjectile : public ARLRActor
{
	GENERATED_BODY()
	
public:
	ARLRProjectile();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	TObjectPtr<class USphereComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	//FX
	//UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	//TObjectPtr<class UNiagaraComponent> NiagaraComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetFireDir(const FVector& ShootDirection);
	void SetSkillRange(const float& Range);

protected:
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void FinishSkill();

protected:
	float SkillRange;
	float MoveDistance;

	TArray<AActor*> OverlappedActors;
};
