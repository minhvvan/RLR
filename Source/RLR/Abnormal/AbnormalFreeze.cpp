// Fill out your copyright notice in the Description page of Project Settings.


#include "AbnormalFreeze.h"
<<<<<<< Updated upstream
#include "Player/PlayerCharacter.h"


UAbnormalFreeze::UAbnormalFreeze()
{
	PrimaryComponentTick.bCanEverTick = true;
	slow = CreateDefaultSubobject<UAbnormalSlow>(TEXT("Slow"));
}

void UAbnormalFreeze::ApplyAbnormal(APlayerCharacter* other, int duration)
{
	if (other->IsA<APlayerCharacter>())
	{
		Player = other;
		Player->BanInput(true);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAbnormalFreeze::RemoveAbnormal, duration, false);
	}
}

void UAbnormalFreeze::RemoveAbnormal()
{
	Player->BanInput(false);
	slow->ApplyAbnormal(Player,1.f);

}
// 프리즈에서 조작 금지 -> 리무브 -> 슬로우 Apply -> Remove 형태로 구성.
=======

// Sets default values for this component's properties
UAbnormalFreeze::UAbnormalFreeze()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbnormalFreeze::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbnormalFreeze::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

>>>>>>> Stashed changes
