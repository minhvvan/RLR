// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalSilence.h"
<<<<<<< Updated upstream
#include "Player/PlayerCharacter.h"


UAbnormalSilence::UAbnormalSilence()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalSilence::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		Player->SetIsAttack(false);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalSilence::RemoveAbnormal, duration, false);
	}
}

void UAbnormalSilence::RemoveAbnormal()
{
	Player->SetIsAttack(true);
	AActor* actor = GetOwner();
	actor->Destroy();
}
=======

// Sets default values for this component's properties
UAbnormalSilence::UAbnormalSilence()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbnormalSilence::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbnormalSilence::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

>>>>>>> Stashed changes
