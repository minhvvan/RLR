// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Action/Skills/ActionSkill_Area.h"
#include "ActionSkill_Area_Meteor.generated.h"

class UNiagaraSystem;

UCLASS()
class RLR_API UActionSkill_Area_Meteor : public UActionSkill_Area
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARLRProjectile> MeteorProjectile;

	UFUNCTION()
	void OnFinishSkill();
	
protected:
	virtual void OnAnimNotifyTriggered() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> GroundHitFX;

	FVector HitPoint;
};