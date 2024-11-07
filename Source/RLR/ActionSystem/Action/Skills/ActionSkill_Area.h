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

	virtual void CancelAction() override;
	virtual void EndAction() override;

protected:
	virtual bool PreActivateAction() override;
	virtual void ActivateAction() override;

	virtual void OnCompletePlayMontage() override;
	virtual void OnAnimNotifyTriggered() override;

	TObjectPtr<ARLRReticle> SpawnedReticle;
};