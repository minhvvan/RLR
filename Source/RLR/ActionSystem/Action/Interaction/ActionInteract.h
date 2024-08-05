// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Action/Action.h"
#include "ActionInteract.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UActionInteract : public UAction
{
	GENERATED_BODY()
	
public:
	UActionInteract();

protected:
	virtual bool PreActivateAction() override;
	virtual void ActivateAction() override;

public:
	virtual void CancelAction() override;
	virtual void EndAction() override;

protected:
};
