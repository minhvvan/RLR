// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalElectric.h"
<<<<<<< Updated upstream
#include "Player/PlayerCharacter.h"

// TODO : ���� ������
UAbnormalElectric::UAbnormalElectric()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalElectric::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalElectric::RemoveAbnormal, duration, false);
	}
}

void UAbnormalElectric::RemoveAbnormal()
{
	AActor* actor = GetOwner();
	actor->Destroy();
}
=======

// Sets default values for this component's properties
UAbnormalElectric::UAbnormalElectric()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbnormalElectric::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbnormalElectric::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

>>>>>>> Stashed changes
