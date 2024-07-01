// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SkillManager.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API USkillManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USkillManager();

public:
	void InitStatic();
	void Init();
	void SkillAttack(int inputID, FVector ClickedPos);

private:
	TArray<TSubclassOf<class APlayerSkill>> OwnSkills;
};