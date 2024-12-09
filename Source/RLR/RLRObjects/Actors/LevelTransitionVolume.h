// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTransitionVolume.generated.h"

class UBoxComponent;

UCLASS()
class RLR_API ALevelTransitionVolume : public AActor
{
	GENERATED_BODY()
	
public:	

	ALevelTransitionVolume();

protected:

	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString TransitionLevelName;

	UPROPERTY()
	class UBoxComponent* TransitionVolume;
};