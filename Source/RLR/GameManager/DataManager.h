// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager/RLRStruct.h"
#include "DataManager.generated.h"

/**
 * 
 */



 class URLRInputConfig;

UCLASS()
class RLR_API UDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:

	virtual void Initialize(FSubsystemCollectionBase& Collection);
	void				MakeSkillDictionary();															//직업 별로 스킬 정보 정리
	

	UFUNCTION(BlueprintCallable)
	FItemData GetItemData(int32 Id);

	UFUNCTION(BlueprintCallable)
	FSkillData GetSkillData(int32 Id);

	UFUNCTION(BlueprintCallable)
	void GetSkillListByJob(ECharacterMainJobType JobType, TArray<FSkillData>& OutArray);

	UFUNCTION(BlueprintCallable)
	URLRInputConfig* GetInputConfig();

	//등급에 따른 배경색
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EItemRarity, TObjectPtr<UTexture2D>> RarityImage;


private:
	UPROPERTY()
	TObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY()
	TObjectPtr<UDataTable> SkillDataTable;

	//캐릭터 직업 별로 스킬 정보를 들고 있는다.
	UPROPERTY()
	TMap<ECharacterMainJobType, FSkillList> SkillDictionary;


private:

	UPROPERTY()
	TObjectPtr<URLRInputConfig> InputConfig;

};
