// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

<<<<<<< Updated upstream
#include "Abnormal.h"
#include "AbnormalBurn.generated.h"

UCLASS()
class RLR_API UAbnormalBurn : public UAbnormal
{
	GENERATED_BODY()

public:
	UAbnormalBurn();

	virtual void ApplyAbnormal(APlayerCharacter* other, int duration) override;

	UFUNCTION()
	virtual void RemoveAbnormal() override;
=======
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbnormalBurn.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RLR_API UAbnormalBurn : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbnormalBurn();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
>>>>>>> Stashed changes
};
