// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Action/Skills/ActionSkill.h"
#include "ActionSkill_Normal.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UActionSkill_Normal : public UActionSkill
{
	GENERATED_BODY()
	
public:
	UActionSkill_Normal();

	virtual void CancelAction();
	virtual void EndAction();

protected:
	virtual bool PreActivateAction();
	virtual void ActivateAction();

	UFUNCTION()
	void OnCompletePlayMontage();

protected:
	UPROPERTY(EditAnywhere)
	float RotationSpeed;
};
