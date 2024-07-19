// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Action/Skills/ActionSkill.h"
#include "ActionSkill_Area.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UActionSkill_Area : public UActionSkill
{
	GENERATED_BODY()

public:
	UActionSkill_Area();

	virtual void CancelAction();
	virtual void EndAction();

protected:
	virtual bool PreActivateAction();
	virtual void ActivateAction();

	virtual void OnCompletePlayMontage();

	TObjectPtr<ARLRReticle> SpawnedReticle;

	UFUNCTION()
	void OnAnimNotified();
};