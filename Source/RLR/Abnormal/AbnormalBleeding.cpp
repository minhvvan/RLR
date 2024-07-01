// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalBleeding.h"
<<<<<<< Updated upstream
#include "Player/PlayerCharacter.h"

//TODO : ���� ������ 
UAbnormalBleeding::UAbnormalBleeding()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalBleeding::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalBleeding::RemoveAbnormal, duration, false);
	}
}

void UAbnormalBleeding::RemoveAbnormal()
{
	AActor* actor = GetOwner();
	actor->Destroy();
}
=======

// Sets default values for this component's properties
UAbnormalBleeding::UAbnormalBleeding()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbnormalBleeding::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbnormalBleeding::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

>>>>>>> Stashed changes
