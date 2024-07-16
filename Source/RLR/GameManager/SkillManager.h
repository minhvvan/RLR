// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "SkillManager.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API USkillManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection);

public:
	void Init();
	void SkillAttack(FGameplayTag TriggerTag);

private:
	TMap<FGameplayTag, TSubclassOf<class UAction>> OwnSkills;

	UPROPERTY()
	TObjectPtr<UDataTable> SkillClassTable;
};