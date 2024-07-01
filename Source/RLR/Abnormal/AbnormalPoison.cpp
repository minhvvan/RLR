// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalPoison.h"
<<<<<<< Updated upstream
#include "Player/PlayerCharacter.h"

//TODO : ���� ������
UAbnormalPoison::UAbnormalPoison()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbnormalPoison::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalPoison::RemoveAbnormal, duration, false);
	}
}

void UAbnormalPoison::RemoveAbnormal()
{
	AActor* actor = GetOwner();
	actor->Destroy();
}
=======

// Sets default values for this component's properties
UAbnormalPoison::UAbnormalPoison()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbnormalPoison::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbnormalPoison::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

>>>>>>> Stashed changes
