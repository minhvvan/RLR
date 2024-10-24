// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Action/Action.h"
#include "ActionAttack.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UActionAttack : public UAction
{
	GENERATED_BODY()

public:
	UActionAttack();

protected:
	virtual bool PreActivateAction() override;
	virtual void ActivateAction() override;

public:
	virtual void CancelAction() override;
	virtual void EndAction() override;

	UFUNCTION()
	void OnCompletePlayMontage();

	virtual void OnAnimNotifyTriggered() override;

protected:
	UPROPERTY(EditAnywhere)
	float RotationSpeed;
};
