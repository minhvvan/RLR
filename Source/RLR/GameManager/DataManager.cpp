// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/DataManager.h"
#include "Player/PlayerCommands.h"
#include "Structs/PlayerStructs.h"



void UDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	//데이터 파일들을 읽어온다.

	ItemDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ItemDataTable.DT_ItemDataTable'")));

	if(IsValid(ItemDataTable) == false)
		DEBUG_LOG("아이템 테이블 로드 실패");

	MonsterDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_MonsterDataTable.DT_MonsterDataTable'")));

	if (IsValid(MonsterDataTable) == false)
		DEBUG_LOG("몬스터 테이블 로드 실패");

	SkillDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_SkillDataTable.DT_SkillDataTable'")));
	
	if (IsValid(SkillDataTable) == false)
		DEBUG_LOG("스킬 테이블 로드 실패");


	MakeSkillDictionary();

	InputConfig = Cast<URLRInputConfig>(StaticLoadObject(URLRInputConfig::StaticClass(), NULL, TEXT("/Script/RLR.RLRInputConfig'/Game/Blueprints/Player/Input/RLRInputConfig.RLRInputConfig'")));
	if (IsValid(InputConfig) == false)
		DEBUG_LOG("키 입력 정보 로드 실패");


	ResourceTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ResourceTable.DT_ResourceTable'")));
	if (IsValid(ResourceTable) == false)
		DEBUG_LOG("텍스쳐 테이블 로드 실패");

	WidgetClassTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_WidgetClassTable.DT_WidgetClassTable'")));
	if (IsValid(WidgetClassTable) == false)
		DEBUG_LOG("위젯 클래스 테이블 로드 실패");

	CharacterClassTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_CharacterClassTable.DT_CharacterClassTable'")));
	if (IsValid(CharacterClassTable) == false)
		DEBUG_LOG("캐릭터 클래스 테이블 로드 실패");	
	
	ObjectClassTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ObjectClassTable.DT_ObjectClassTable'")));
	if (IsValid(ObjectClassTable) == false)
		DEBUG_LOG("오브젝트 클래스 테이블 로드 실패");
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
			//TODO: ECharacterMainJobType 분리 후 변경 필요
			ECharacterMainJobType MainJob = ECharacterMainJobType::NONE;

			if (SkillDictionary.Contains(MainJob) == false)
			{
				SkillDictionary.Add(MainJob, FSkillList());
			}

			FSkillList& SkillList = SkillDictionary[MainJob];

			if (SkillDictionary[MainJob].Contains(SkillData->SkillId) == true)
			{
				Util::Checkf(nullptr, TEXT("스킬 데이터 테이블에 중복된 Skill ID가 존재합니다."));
				continue;
			}

			SkillList.Add(*SkillData);
		}
	}
}

FItemData UDataManager::GetItemData(int32 Seq)
{
	if (ItemDataTable)
	{
		FItemData* Data = ItemDataTable->FindRow<FItemData>(*FString::FromInt(Seq), TEXT(""));
		if(Data == nullptr)
			return FItemData();

		return *Data;
	}


	return FItemData();
}

const FSkillData& UDataManager::GetSkillData(int32 Seq)
{
	if (SkillDataTable)
	{
		FSkillData* Data = SkillDataTable->FindRow<FSkillData>(*FString::FromInt(Seq), TEXT(""));
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

	OutArray = SkillDictionary[JobType].toArray();
}

const FMonsterStatus& UDataManager::GetMonsterData(int32 Seq)
{
	if (MonsterDataTable)
	{
		FMonsterStatus* Data = MonsterDataTable->FindRow<FMonsterStatus>(*FString::FromInt(Seq), TEXT(""));
		if (Data == nullptr)
			return FMonsterStatus::EmptyMonsterData;

		return *Data;
	}

	return FMonsterStatus::EmptyMonsterData;
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

FResourceData UDataManager::GetResource(FString Name)
{
	if (IsValid(ResourceTable) == true)
	{
		const FResourceData* Data = ResourceTable->FindRow<FResourceData>(*Name, TEXT(""));
		if (Data == nullptr)
			return FResourceData();

		return *Data;
	}

	return FResourceData();
}
