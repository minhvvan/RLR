// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRObjects/Actors/LevelTransitionVolume.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "GameManager/GameManager.h"
#include "GameManager/LevelManager.h"

// Sets default values
ALevelTransitionVolume::ALevelTransitionVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TransitionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransitionVolume"));
	RootComponent = TransitionVolume;
	TransitionVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
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

