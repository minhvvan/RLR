// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalBind.h"
<<<<<<< Updated upstream
#include "Player/PlayerCharacter.h"

UAbnormalBind::UAbnormalBind()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalBind::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		Player->SetMoveMode(MOVE_None);

		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalBind::RemoveAbnormal, duration, false);
	}
}

void UAbnormalBind::RemoveAbnormal()
{
	Player->SetMoveMode(MOVE_Walking);

	AActor* actor = GetOwner();
	actor->Destroy();
}
=======

// Sets default values for this component's properties
UAbnormalBind::UAbnormalBind()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbnormalBind::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbnormalBind::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

>>>>>>> Stashed changes
