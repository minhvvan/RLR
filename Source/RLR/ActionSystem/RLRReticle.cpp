// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/RLRReticle.h"
#include "Player/RLRPlayerController.h"
#include "Components/DecalComponent.h"
#include "GameManager/LiteralManager.h"

// Sets default values
ARLRReticle::ARLRReticle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Decal = CreateDefaultSubobject<UDecalComponent>(RLRLITERAL.RLRReticle_Decal);
	SetRootComponent(Decal);

	FRotator Rot(90.f, 0.f, 0.f);
	Decal->SetWorldRotation(Rot.Quaternion());
}

// Called when the game starts or when spawned
void ARLRReticle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARLRReticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (OwnerPC)
	{
		FVector MousePos = OwnerPC->GetClickPosition();
		SetActorLocation(MousePos);
	}
}

void ARLRReticle::InitializeReticle(ARLRPlayerController* PlayerController, float SkillRadius)
{
	AddTickPrerequisiteActor(PlayerController);
	OwnerPC = PlayerController;
	Decal->DecalSize = FVector(SkillRadius);
}