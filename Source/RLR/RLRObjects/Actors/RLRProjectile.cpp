// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRObjects/Actors/RLRProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameManager/EffectManager.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "RLR.h"

ARLRProjectile::ARLRProjectile():
	SkillRange(0.f),
	MoveDistance(0.f)
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	SetRootComponent(CollisionComponent);

	CollisionComponent->InitSphereRadius(100.f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

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

	if (MoveDistance >= SkillRange)
	{
		FinishSkill();
	}
}

void ARLRProjectile::SetFireDir()
{
	if (!ProjectileMovement) return;

	ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;
}

void ARLRProjectile::SetSkillRange(const float& Range)
{
	SkillRange = Range;
}

void ARLRProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == Owner) return;

	RLR_LOG(LogRLR, Log, TEXT("Overlapped Actor: %s"), *OtherActor->GetName());
	OverlappedActors.Add(OtherActor);
	UEffectManager* EffectManager = GetGameInstance()->GetSubsystem<UEffectManager>();
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
	RLR_LOG(LogRLR, Log, TEXT("Overlapped: %d"), OverlappedActors.Num());

	OnFinishSkill.Broadcast(OverlappedActors);
	Destroy();
}
