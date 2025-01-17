// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLRObjects/Actors/RLRActor.h"
#include "RLRProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishSkill);

struct FSkillData;

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetFireDirection(FVector dir);

	void SetSkillData(TSharedPtr<FSkillData> Data);
	FOnFinishSkill OnFinishSkill;

protected:
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void FinishSkill();
	void SetSkillDistance(const float& Distance);

protected:
	float SkillDistance;
	float MoveDistance;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 2000;
	FVector FireDir;

	TSharedPtr<FSkillData> SkillData;
	TArray<AActor*> OverlappedActors;
};
