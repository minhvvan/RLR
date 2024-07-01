// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

<<<<<<< Updated upstream
#include "Abnormal.h"
#include "AbnormalStun.generated.h"

UCLASS()
class RLR_API UAbnormalStun : public UAbnormal
=======
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbnormalStun.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RLR_API UAbnormalStun : public UActorComponent
>>>>>>> Stashed changes
{
	GENERATED_BODY()

public:	
<<<<<<< Updated upstream
	UAbnormalStun();

	virtual void ApplyAbnormal(APlayerCharacter* Player, int duration) override;
	
	UFUNCTION()
	virtual void RemoveAbnormal() override;
=======
	// Sets default values for this component's properties
	UAbnormalStun();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
>>>>>>> Stashed changes
};
