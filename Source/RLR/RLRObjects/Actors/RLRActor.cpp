// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRObjects/Actors/RLRActor.h"
#include "ActionSystem/ActionSystemComponent.h"

// Sets default values
ARLRActor::ARLRActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ASC=CreateDefaultSubobject<UActionSystemComponent>(TEXT("ASC"));
}

UActionSystemComponent* ARLRActor::GetActionSystemComponent() const
{
	return ASC.Get();
}

// Called when the game starts or when spawned
void ARLRActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARLRActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}