// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalBurn.h"
<<<<<<< Updated upstream
#include "Player/PlayerCharacter.h"

//TODO : 지속 데미지
UAbnormalBurn::UAbnormalBurn()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalBurn::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalBurn::RemoveAbnormal, duration, false);
	}
}

void UAbnormalBurn::RemoveAbnormal()
{
	AActor* actor = GetOwner();
	actor->Destroy();
}
=======

// Sets default values for this component's properties
UAbnormalBurn::UAbnormalBurn()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbnormalBurn::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbnormalBurn::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

>>>>>>> Stashed changes
