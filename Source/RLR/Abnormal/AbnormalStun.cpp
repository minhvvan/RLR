// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalStun.h"
<<<<<<< Updated upstream
#include "Player/PlayerCharacter.h"


UAbnormalStun::UAbnormalStun()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalStun::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalStun::RemoveAbnormal, duration, false);
	}
}

void UAbnormalStun::RemoveAbnormal()
{
	Player->BanInput(false);

	AActor* actor = GetOwner();
	actor->Destroy();
=======

// Sets default values for this component's properties
UAbnormalStun::UAbnormalStun()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbnormalStun::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbnormalStun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
>>>>>>> Stashed changes
}

