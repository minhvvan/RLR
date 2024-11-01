// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Action/Action.h"
#include "ActionPlayMontage.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UActionPlayMontage : public UAction
{
	GENERATED_BODY()

public:
	UActionPlayMontage();

protected:
	virtual bool PreActivateAction();
	virtual void ActivateAction();

public:
	virtual void CancelAction();
	virtual void EndAction();

protected:
	UFUNCTION()
	void OnCompletePlayMontage();
};
