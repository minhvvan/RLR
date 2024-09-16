// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager/RLRStruct.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Structs/SkillStructs.h"
#include "Structs/UtilStructs.h"
#include "RLR.h"
#include "Structs/LevelStruct.h"
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
	void MakeSkillDictionary();															//직업 별로 스킬 정보 정리
	

	UFUNCTION(BlueprintCallable)
	FItemData				GetItemData(int32 Seq);

	UFUNCTION(BlueprintCallable)
	const FMonsterStatus&	GetMonsterData(int32 Seq);

	UFUNCTION(BlueprintCallable)
	const FSkillData&		GetSkillData(int32 Seq);

	UFUNCTION(BlueprintCallable)
	void					GetSkillListByJob(ECharacterMainJobType JobType, TArray<FSkillData>& OutArray);

	UFUNCTION(BlueprintCallable)
	const FLevelData&		GetLevelData(int32 Seq);

	UFUNCTION(BlueprintCallable)
	const FExpTable&		GetExpData(int32 Seq);

	/*
	
		Etc

	*/

	UFUNCTION(BlueprintCallable)
	URLRInputConfig*		GetInputConfig();

	UFUNCTION(BlueprintCallable)
	FResourceData			GetResource(FString Name);


	/*
		Template
	*/

	template<typename T>
	TSubclassOf<T>			GetWidgetClass(FString Name);

	template<typename T>
	TSubclassOf<T>			GetCharacterClass(FString Name);

	template<typename T>
	TSubclassOf<T>			GetObjectClass(FString Name);	
	
	template<typename T>
	TSubclassOf<T>			GetMonsterClass(int32 MonsterSeq);

	//등급에 따른 배경색
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EItemRarity, TObjectPtr<UTexture2D>> RarityImage;

private:
	UPROPERTY()
	TObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY()
	TObjectPtr<UDataTable> SkillDataTable;

	UPROPERTY()
	TObjectPtr<UDataTable> MonsterDataTable;

	UPROPERTY()
	TObjectPtr<UDataTable> LevelDataTable;

	//캐릭터 직업 별로 스킬 정보를 들고 있는다.
	FSkillDictionary<ECharacterMainJobType, FSkillList> SkillDictionary;

	//각종 리소스 테이블.
	UPROPERTY()
	TObjectPtr<UDataTable> ResourceTable;

	UPROPERTY()
	TObjectPtr<UDataTable> WidgetClassTable;

	UPROPERTY()
	TObjectPtr<UDataTable> CharacterClassTable;

	UPROPERTY()
	TObjectPtr<UDataTable> ObjectClassTable;

	UPROPERTY()
	TObjectPtr<UDataTable> MonsterClassTable;

	UPROPERTY()
	TObjectPtr<UDataTable> ExpDataTable;

private:

	UPROPERTY()
	TObjectPtr<URLRInputConfig> InputConfig;
};

template<typename T>
inline TSubclassOf<T> UDataManager::GetWidgetClass(FString Name)
{
	if (IsValid(WidgetClassTable) == true)
	{
		const FClassData* Data = WidgetClassTable->FindRow<FClassData>(*Name, TEXT(""));
		if(Data == nullptr)
		{ 
			DEBUG_LOG("UDataManager::GetWidgetClass Error. Data is Null. DT_WidgetClassTable에 데이터를 넣어주세요.");
			return nullptr;
		}

		if (Data->RLRClass->IsChildOf(T::StaticClass()))
		{
			return TSubclassOf<T>(Data->RLRClass);
		}
	}

	DEBUG_LOG("UDataManager::GetWidgetClass Error. DT_WidgetClassTable is Null. DT_WidgetClassTable의 위치를 확인해주세요.");
	return nullptr;
}

template<typename T>
inline TSubclassOf<T> UDataManager::GetCharacterClass(FString Name)
{
	if (IsValid(CharacterClassTable) == true)
	{
		const FClassData* Data = CharacterClassTable->FindRow<FClassData>(*Name, TEXT(""));
		if (Data == nullptr)
		{
			DEBUG_LOG("UDataManager::GetCharacterClass Error. FClassData is Null. DT_CharacterClassTable에 데이터를 넣어주세요.");
			return nullptr;
		}

		if (Data->RLRClass->IsChildOf(T::StaticClass()))
		{
			return TSubclassOf<T>(Data->RLRClass);
		}
	}

	DEBUG_LOG("UDataManager::GetCharacterClass Error. DT_CharacterClassTable is Null. DT_CharacterClassTable의 위치를 확인해주세요.");
	return nullptr;
}


template<typename T>
inline TSubclassOf<T> UDataManager::GetObjectClass(FString Name)
{
	if (IsValid(ObjectClassTable) == true)
	{
		const FClassData* Data = ObjectClassTable->FindRow<FClassData>(*Name, TEXT(""));
		if (Data == nullptr)
		{
			RLR_LOG(LogRLR, Log, TEXT("FClassData is Null."));
			return nullptr;
		}

		if (Data->RLRClass->IsChildOf(T::StaticClass()))
		{
			return TSubclassOf<T>(Data->RLRClass);
		}
	}

	DEBUG_LOG("ObjectClassTable is Null.");
	return nullptr;
}

template<typename T>
inline TSubclassOf<T> UDataManager::GetMonsterClass(int32 MonsterSeq)
{
	if (IsValid(MonsterClassTable) == true)
	{
		const FClassData* Data = MonsterClassTable->FindRow<FClassData>(*FString::FormatAsNumber(MonsterSeq), TEXT(""));
		if (Data == nullptr)
		{
			RLR_LOG(LogRLR, Log, TEXT("FClassData is Null."));
			return nullptr;
		}

		if (Data->RLRClass->IsChildOf(T::StaticClass()))
		{
			return TSubclassOf<T>(Data->RLRClass);
		}
	}

	DEBUG_LOG("MonsterClassTable is Null.");
	return nullptr;
}
