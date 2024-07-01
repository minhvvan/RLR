// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

<<<<<<< Updated upstream
#include "Abnormal.h"
#include "AbnormalSilence.generated.h"

UCLASS()
class RLR_API UAbnormalSilence : public UAbnormal
{
	GENERATED_BODY()

public:
	UAbnormalSilence();

	virtual void ApplyAbnormal(APlayerCharacter* other, int duration) override;

	UFUNCTION()
	virtual void RemoveAbnormal() override;
=======
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbnormalSilence.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RLR_API UAbnormalSilence : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbnormalSilence();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
>>>>>>> Stashed changes
};
