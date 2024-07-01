// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalStiffen.h"
<<<<<<< Updated upstream
#include "Player/PlayerCharacter.h"


UAbnormalStiffen::UAbnormalStiffen()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalStiffen::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalStiffen::RemoveAbnormal, duration, false);
	}
}

void UAbnormalStiffen::RemoveAbnormal()
{
	Player->BanInput(false);

	AActor* actor = GetOwner();
	actor->Destroy();
}
=======

// Sets default values for this component's properties
UAbnormalStiffen::UAbnormalStiffen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbnormalStiffen::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbnormalStiffen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

>>>>>>> Stashed changes
