// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLRObjects/Actors/RLRActor.h"
#include "GameManager/RLRStruct.h"
#include "RLRInteractableActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UWidgetComponent;

UCLASS()
class RLR_API ARLRInteractableActor : public ARLRActor
{
	GENERATED_BODY()

public:
	ARLRInteractableActor();

	void SetInteractData(const FInteractData& Data);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> InteractionComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> InteractUI;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere, Category = Action)
	TSubclassOf<UAction> GiveToPlayerAction;

	TSharedPtr<FInteractData> InteractData;
};