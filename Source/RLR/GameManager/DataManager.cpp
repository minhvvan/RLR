// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/DataManager.h"
#include "Player/PlayerCommands.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void UDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	//데이터 파일들을 읽어온다.

	ItemDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ItemDataTable.DT_ItemDataTable'")));

	DEBUG_LOG("아이템 테이블 로드 실패");

	SkillDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_SkillDataTable.DT_SkillDataTable'")));
	
	DEBUG_LOG("스킬 테이블 로드 실패");

	MakeSkillDictionary();

	InputConfig = Cast<URLRInputConfig>(StaticLoadObject(URLRInputConfig::StaticClass(), NULL, TEXT("/Script/RLR.RLRInputConfig'/Game/Blueprints/Player/Input/RLRInputConfig.RLRInputConfig''")));

	//DEBUG_LOG("키 정보 로드 실패");

}

void UDataManager::MakeSkillDictionary()
{
	if(IsValid(SkillDataTable) == false)
		return;

	TArray<FSkillData*> AllSkillData;
	SkillDataTable->GetAllRows<FSkillData>(TEXT(""), AllSkillData);

	// 행 데이터 처리
	for (const FSkillData* SkillData : AllSkillData)
	{
		if (SkillData)
		{
			ECharacterMainJobType MainJob = SkillData->MainJobType;

			if (SkillDictionary.Contains(MainJob) == false)
			{
				SkillDictionary.Add(MainJob, FSkillList());
			}

			FSkillList& SkillList = SkillDictionary[MainJob];

			if (SkillList.SkillList.Contains(SkillData->SkillId) == true)
			{
				Util::Checkf(nullptr, TEXT("스킬 데이터 테이블에 중복된 Skill ID가 존재합니다."));
				continue;
			}

			SkillList.SkillList.Add(SkillData->SkillId, *SkillData);
		}
	}
}

FItemData UDataManager::GetItemData(int32 Id)
{
	if (ItemDataTable)
	{
		FItemData* Data = ItemDataTable->FindRow<FItemData>(*FString::FromInt(Id), TEXT(""));
		if(Data == nullptr)
			return FItemData();

		return *Data;
	}


	return FItemData();
}

FSkillData UDataManager::GetSkillData(int32 Id)
{
	if (SkillDataTable)
	{
		FSkillData* Data = SkillDataTable->FindRow<FSkillData>(*FString::FromInt(Id), TEXT(""));
		if(Data == nullptr)
			return FSkillData::EmptySkillData;

		return * Data;
	}

	return FSkillData::EmptySkillData;
}

void UDataManager::GetSkillListByJob(ECharacterMainJobType JobType, TArray<FSkillData>& OutArray)
{
	if(SkillDictionary.Contains(JobType) == false)
		return;

	SkillDictionary[JobType].SkillList.GenerateValueArray(OutArray);
}

URLRInputConfig* UDataManager::GetInputConfig()
{
	if (IsValid(InputConfig) == false)
	{
		DEBUG_LOG("GetInputConfig Error. InputConfig is Null");
		return nullptr;
	}

	return InputConfig;
}
