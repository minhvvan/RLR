// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Action/Skills/ActionSkill.h"
#include "ActionSkill_Holding_Skill.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UActionSkill_Holding_Skill : public UActionSkill
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARLRProjectile> HoldingSkillProjectile;
	FTimerHandle ProjectileSpawnTimerHandle;

protected:
	virtual void ActivateAction();
};
