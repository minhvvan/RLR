// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RLRReticle.generated.h"

UCLASS()
class RLR_API ARLRReticle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARLRReticle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitializeReticle(class AUserController* PlayerController, float SkillRadius);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AUserController> OwnerPC;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDecalComponent> Decal;
};
