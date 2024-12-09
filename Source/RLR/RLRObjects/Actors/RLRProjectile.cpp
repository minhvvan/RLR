// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRObjects/Actors/RLRProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameManager/EffectManager.h"
#include "GameManager/SkillManager.h"
#include "GameManager/LiteralManager.h"
#include "GameManager/GameManager.h"
#include "Structs/SkillStructs.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "RLR.h"

ARLRProjectile::ARLRProjectile():
	SkillDistance(0.f),
	MoveDistance(0.f)
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(RLRLITERAL.Projectile_CollisionComponent);
	SetRootComponent(CollisionComponent);

	CollisionComponent->InitSphereRadius(100.f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(RLRLITERAL.Projectile_Mesh);
	Mesh->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(RLRLITERAL.Projectile_Movement);

	//Temp
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;


}

void ARLRProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ARLRProjectile::OnOverlap);
}

void ARLRProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveDistance += ProjectileMovement->InitialSpeed * DeltaTime;

	if (MoveDistance >= SkillDistance)
	{
		FinishSkill();
	}
}

void ARLRProjectile::SetSkillData(TSharedPtr<FSkillData> Data)
{
	SkillData = Data;
	SetSkillDistance(SkillData->SkillDistance);
}

void ARLRProjectile::SetSkillDistance(const float& Range)
{
	SkillDistance = Range;
}

void ARLRProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == Owner) return;

	auto* EffectManager = GameInstance->GetEffectManager();
	auto* SkillManager = GameInstance->GetSkillManager();

	OverlappedActors.Add(OtherActor);
	if (SkillManager->RequestSkillResult(SkillData.Get(), OverlappedActors))
	{
		OverlappedActors.Empty();
	}
	
	if (EffectManager)
	{
		FVector effectLocation = (OtherActor->GetActorLocation() - SweepResult.Location) / 2;
		EffectManager->SpawnPlayerHitEffect(OtherActor->GetActorLocation() - effectLocation);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EffectManager is null!"));
	}
}

void ARLRProjectile::FinishSkill()
{
	Destroy();
}
