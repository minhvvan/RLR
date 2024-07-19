// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Action/Skills/ActionSkill.h"
#include "ActionSkill_Normal_SwordAura.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UActionSkill_Normal_SwordAura : public UActionSkill
{
	GENERATED_BODY()
	
public:
	UActionSkill_Normal_SwordAura();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARLRProjectile> SwordAuraProjectile;

protected:
	virtual void ActivateAction();

	UFUNCTION()
	void OnFinishSkill(TArray<AActor*> OverlappedActor);
};
