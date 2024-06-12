// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_Explosion.h"

// Sets default values
ASkill_Explosion::ASkill_Explosion()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Init();
}

void ASkill_Explosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	spawnTime += DeltaTime;

	if (spawnTime >= 0.8f)
	{
		UE_LOG(LogTemp, Log, TEXT("end life"));

		Destroy();
	}
}

void ASkill_Explosion::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	spawnTime = 0.f;

	switch (EndPlayReason)
	{
	case EEndPlayReason::Destroyed:
		UE_LOG(LogTemp, Warning, TEXT("Actor is destroyed"));
		break;
	case EEndPlayReason::LevelTransition:
		UE_LOG(LogTemp, Warning, TEXT("Actor removed due to level transition"));
		break;
	case EEndPlayReason::EndPlayInEditor:
		UE_LOG(LogTemp, Warning, TEXT("End play in editor"));
		break;
	case EEndPlayReason::RemovedFromWorld:
		UE_LOG(LogTemp, Warning, TEXT("Actor removed from world"));
		break;
	case EEndPlayReason::Quit:
		UE_LOG(LogTemp, Warning, TEXT("Game is quitting"));
		break;
	default:
		break;
	}
}

void ASkill_Explosion::SkillAttack(FVector position, UParticleSystem* particle)
{
	if (particle)
	{
		particle = GetAttackParticle();
		UParticleSystemComponent* particleSystem;
		particleSystem = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, position);
		FVector particlePosition = particleSystem->GetComponentLocation();
	}

	// Create Actor 
	GetWorld()->SpawnActor<ASkill_Explosion>(ASkill_Explosion::StaticClass(), position, FRotator::ZeroRotator);
}

void ASkill_Explosion::Init()
{
	//생성자에서 파티클 null 체크 
	if (!Attack)
	{
		ConstructorHelpers::FObjectFinder<UParticleSystem>particle(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
		if (particle.Succeeded())
		{
			Attack = particle.Object;
		}
	}

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;
	Damage = 10;
	CollisionRange = FVector(2.f);
	Collision->SetWorldScale3D(CollisionRange);
	spawnTime = 0.f;
}