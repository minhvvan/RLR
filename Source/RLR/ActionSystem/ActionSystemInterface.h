// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActionSystemInterface.generated.h"

class UActionSystemComponent;

UINTERFACE(MinimalAPI)
class UActionSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RLR_API IActionSystemInterface
{
	GENERATED_BODY()

public:
	virtual UActionSystemComponent* GetActionSystemComponent() const=0;
};
