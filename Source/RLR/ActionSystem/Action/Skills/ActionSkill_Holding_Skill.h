// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Action/Skills/ActionSkill_Holding.h"
#include "ActionSkill_Holding_Skill.generated.h"

UCLASS()
class RLR_API UActionSkill_Holding_Skill : public UActionSkill_Holding
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARLRProjectile> HoldingSkillProjectile;
	FTimerHandle ProjectileSpawnTimerHandle;

	virtual void OnAnimNotifyTriggered();
};
