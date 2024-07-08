// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLRObjects/Characters/RLRNonPlayerCharacter.h"
#include "RLRMonster.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API ARLRMonster : public ARLRNonPlayerCharacter
{
	GENERATED_BODY()
	
public:
	ARLRMonster();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
};
 