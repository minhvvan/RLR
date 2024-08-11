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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatedActionTag, FGameplayTag, ActionTag);


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

	//Response
	void SetSelectedSkills(TArray<FSkillData>& SelectedSkills);

	//Request to Server
	bool RequestGetSelectedSkills();
	bool RequestSkillResult(const FSkillData* SkillData, TArray<AActor*> OverlappedActor);

private:
	TMap<FGameplayTag, FSkillData*> OwnSkills;

	UPROPERTY()
	TObjectPtr<UDataTable> SkillClassTable;

public:

	//현재는 StatusDisplay에서 스킬 사용시, 쿨타임 효과를 재생하기 위해 호출하는 중이다.
	FUpdatedActionTag UpdatedTryActivateAction;
};