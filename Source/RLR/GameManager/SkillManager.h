// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "GameManager/RLRStruct.h"
#include "Structs/SkillStructs.h"
#include "Structs/ItemStructs.h"
#include "SkillManager.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatedActionTag, FGameplayTag, ActionTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatedTest, TArray<FSkillData>&, SkillList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdatedSkillManager);

UCLASS()
class RLR_API USkillManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection);

public:
	void SkillStart(FGameplayTag TriggerTag);
	void SkillAttack(FGameplayTag TriggerTag);
	void SkillComplete(FGameplayTag TriggerTag);
	
	const FSkillData* GetSkillData(FGameplayTag TriggerTag);
	const FSkillDictionary<FGameplayTag, FSkillData>& GetOwnSkills();
	bool HasSkillTag(FGameplayTag TriggerTag);
	bool HasLearnedSkill(int32 SkillSeq);

	//Response
	UFUNCTION()
	void SetLearnedSkills(const TArray<FSkillData>& LearnedSkillsList);

	//Request to Server
	bool RequestSkillResult(const FSkillData* SkillData, TArray<AActor*> OverlappedActor);

	//아이템 사용
	void UsingItem(FGameplayTag TriggerTag);

	const FItemData* GetItemData(FGameplayTag TriggerTag);
	const FSkillDictionary<FGameplayTag, FItemData>& GetOwnItems();
	bool HasItemTag(FGameplayTag TriggerTag);

	UFUNCTION()
	void SetSelectedItems(TArray<FItemData>& SelectedItems);

protected:
	UFUNCTION()
	void SetSelectedSkills(TArray<FSkillData>& SelectedSkills);

private:
	FSkillDictionary<FGameplayTag, FSkillData> OwnSkills;
	FSkillDictionary<FGameplayTag, FItemData> OwnItems;

	UPROPERTY()
	TMap<int32, FSkillData> LearnedSkills;

public:

	//현재는 StatusDisplay에서 스킬 사용시, 쿨타임 효과를 재생하기 위해 호출하는 중이다.
	FUpdatedActionTag UpdatedTryActivateAction;
	FUpdatedActionTag UpdatedTryUsingItemAction;

	/*
			1.스킬 퀵 슬롯 위치가 바뀌면 업데이트
	*/
	FUpdatedSkillManager UpdatedSkillSettingDelegate;
	void UpdatedSkillSettingBroadcast();

	/*
			1.아이템 퀵 슬롯 위치 바뀌면 업데이트
	*/
	FUpdatedSkillManager UpdatedItemSettingDelegate;
	void UpdatedItemSettingBroadcast();

	FUpdatedTest		UpdateTest;
};


