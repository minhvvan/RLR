// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

<<<<<<< Updated upstream
#include "Abnormal.h"
#include "AbnormalBleeding.generated.h"

UCLASS()
class RLR_API UAbnormalBleeding : public UAbnormal
{
	GENERATED_BODY()

public:
	UAbnormalBleeding();

	virtual void ApplyAbnormal(APlayerCharacter* other, int duration) override;

	UFUNCTION()
	virtual void RemoveAbnormal() override;
=======
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbnormalBleeding.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RLR_API UAbnormalBleeding : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbnormalBleeding();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
>>>>>>> Stashed changes
};
