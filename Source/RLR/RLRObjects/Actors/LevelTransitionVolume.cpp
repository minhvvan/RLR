// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRObjects/Actors/LevelTransitionVolume.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "GameManager/GameManager.h"
#include "GameManager/LevelManager.h"
#include "GameManager/LiteralManager.h"

ALevelTransitionVolume::ALevelTransitionVolume()
{
	PrimaryActorTick.bCanEverTick = true;

	TransitionVolume = CreateDefaultSubobject<UBoxComponent>(RLRLITERAL.TransitionVolume_VolumeName);
	RootComponent = TransitionVolume;
	TransitionVolume->SetCollisionProfileName(RLRLITERAL.TransitionVolume_OverlapOnlyPawn);
}

// Called when the game starts or when spawned
void ALevelTransitionVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALevelTransitionVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
    ARLRPlayerCharacter* Character = Cast<ARLRPlayerCharacter>(OtherActor);
    if (Character)
    {
		GameInstance->GetLevelManager()->LoadLevel(FName(TransitionLevelName));
    }
}

