// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_Explosion.h"

// Sets default values
ASkill_Explosion::ASkill_Explosion()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Init();
}

void ASkill_Explosion::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ASkill_Explosion::OnDestroty, Data.ActivityTime, false);
}

void ASkill_Explosion::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	spawnTime = 0.f;

	switch (EndPlayReason)
	{
	case EEndPlayReason::Destroyed:
		SetIsHit(false);
		GetWorld()->GetTimerManager().ClearTimer(Timer);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("Actor Destroy"));
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
	if (!particle)
	{
		particle = GetAttackParticle();
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, position);
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
	Abnormal = CreateDefaultSubobject<UAbnormalSilence>(TEXT("Abnormal"));
	RootComponent = Collision;
	Data.Damage = 10;
	Data.Duration = 2;
	Data.ActivityTime = 0.8f;
	Data.CollisionRange = FVector(2.f);
	Collision->SetWorldScale3D(Data.CollisionRange);
	spawnTime = 0.f;
}

