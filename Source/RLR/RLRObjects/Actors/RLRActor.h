// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RLRObjects/ActionSystemInterface.h"
#include "GameplayTagContainer.h"
#include "RLRActor.generated.h"

class UAction;

UCLASS()
class RLR_API ARLRActor : public AActor, public IActionSystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARLRActor();

	virtual UActionSystemComponent* GetActionSystemComponent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category=ASC , meta=( AllowPrivateAccess="true" ));
	TWeakObjectPtr<UActionSystemComponent> ASC;

	UPROPERTY(EditAnywhere , Category=Action)
	TMap<FGameplayTag , TSubclassOf<UAction>> DefaultActions;
};
