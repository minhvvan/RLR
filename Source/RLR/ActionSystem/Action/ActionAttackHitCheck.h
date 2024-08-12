// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Action/Action.h"
#include "GameManager/RLRStruct.h"
#include "ActionAttackHitCheck.generated.h"


/**
 * 
 */
UCLASS()
class RLR_API UActionAttackHitCheck : public UAction
{
	GENERATED_BODY()

public:
	UActionAttackHitCheck();
	const FSkillData* SkillData;
protected:
	virtual void ActivateAction();

public:
	virtual void CancelAction();
	virtual void EndAction();
};
