// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ActionSystem/ActionSystemInterface.h"
#include "GameplayTagContainer.h"
#include "RLRCharacter.generated.h"

class UAction;
class UActionSystemComponent;

UCLASS(Blueprintable)
class ARLRCharacter : public ACharacter, public IActionSystemInterface
{
	GENERATED_BODY()

public:
	ARLRCharacter();

	virtual UActionSystemComponent* GetActionSystemComponent() const;
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, Category=Action , meta=( AllowPrivateAccess="true" ));
	TObjectPtr<UActionSystemComponent> ASC;

	UPROPERTY(EditAnywhere , Category=Action)
	TMap<FGameplayTag , TSubclassOf<UAction>> DefaultActions;
};