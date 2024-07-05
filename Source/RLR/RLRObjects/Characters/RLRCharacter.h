// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RLRObjects/ActionSystemInterface.h"
#include "GameplayTagContainer.h"
#include "RLRCharacter.generated.h"

class UAction;

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
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category=ASC , meta=( AllowPrivateAccess="true" ));
	TWeakObjectPtr<UActionSystemComponent> ASC;

	UPROPERTY(EditAnywhere , Category=Action)
	TMap<FGameplayTag , TSubclassOf<UAction>> DefaultActions;
};