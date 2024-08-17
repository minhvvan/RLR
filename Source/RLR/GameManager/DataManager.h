// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager/RLRStruct.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
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
	FItemData				GetItemData(int32 Id);

	UFUNCTION(BlueprintCallable)
	FSkillData				GetSkillData(int32 Id);

	UFUNCTION(BlueprintCallable)
	void					GetSkillListByJob(ECharacterMainJobType JobType, TArray<FSkillData>& OutArray);

	UFUNCTION(BlueprintCallable)
	URLRInputConfig*		GetInputConfig();

	UFUNCTION(BlueprintCallable)
	FResourceData			GetResource(FString Name);

	template<typename T>
	TSubclassOf<T>			GetClass(FString Name);

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

	//각종 리소스 테이블.
	UPROPERTY()
	TObjectPtr<UDataTable> ResourceTable;

	UPROPERTY()
	TObjectPtr<UDataTable> ClassTable;

private:

	UPROPERTY()
	TObjectPtr<URLRInputConfig> InputConfig;
};

template<typename T>
inline TSubclassOf<T> UDataManager::GetClass(FString Name)
{
	if (IsValid(ClassTable) == true)
	{
		const FClassData* Data = ClassTable->FindRow<FClassData>(*Name, TEXT(""));
		if(Data == nullptr)
		{ 
			DEBUG_LOG("UDataManager::GetClass Error. Data is Null. DT_ClassTable에 데이터를 넣어주세요.");
			return nullptr;
		}

		if (Data->RLRClass->IsChildOf(T::StaticClass()))
		{
			return TSubclassOf<T>(Data->RLRClass);
		}
	}

	DEBUG_LOG("UDataManager::GetClass Error. DT_ClassTable is Null. DT_ClassTable의 위치를 확인해주세요.");
	return nullptr;
}
