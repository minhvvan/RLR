// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Action/Action.h"
#include "ActionJump.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UActionJump : public UAction
{
	GENERATED_BODY()

public:
	UActionJump();
	
protected:
	virtual void ActivateAction() override;

public:
	virtual void CancelAction() override;
	virtual void EndAction() override;
};
