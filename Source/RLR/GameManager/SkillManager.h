// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "GameManager/RLRStruct.h"
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
	void SkillComplete(FGameplayTag TriggerTag);

	const FSkillData* GetSkillData(FGameplayTag TriggerTag);
	bool HasSkillTag(FGameplayTag TriggerTag);

private:
	TMap<FGameplayTag, FSkillData*> OwnSkills;

	UPROPERTY()
	TObjectPtr<UDataTable> SkillClassTable;
};