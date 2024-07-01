// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalProvoke.h"
<<<<<<< Updated upstream
#include "Player/PlayerCharacter.h"


UAbnormalProvoke::UAbnormalProvoke()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalProvoke::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		//TODO : 스킬과 몬스터 구현 후 로직 구성.
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalProvoke::RemoveAbnormal, duration, false);
	}
}

void UAbnormalProvoke::RemoveAbnormal()
{
	Player->BanInput(false);

	AActor* actor = GetOwner();
	actor->Destroy();
}
=======

// Sets default values for this component's properties
UAbnormalProvoke::UAbnormalProvoke()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbnormalProvoke::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbnormalProvoke::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

>>>>>>> Stashed changes
