// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/DataManager.h"
#include "GameManager/LevelManager.h"
#include "Player/PlayerCommands.h"
#include "Structs/PlayerStructs.h"
#include "Structs/ItemStructs.h"
#include "Structs/MonsterStructs.h"

void UDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	//데이터 파일들을 읽어온다.

	ItemDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ItemData.DT_ItemData'")));

	if(IsValid(ItemDataTable) == false)
		DEBUG_LOG("아이템 테이블 로드 실패");

	ItemResourceTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ItemResource.DT_ItemResource'")));

	if (IsValid(ItemResourceTable) == false)
		DEBUG_LOG("아이템 리소스 테이블 로드 실패");

	MonsterDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_MonsterDataTable.DT_MonsterDataTable'")));

	if (IsValid(MonsterDataTable) == false)
		DEBUG_LOG("몬스터 테이블 로드 실패");

	SkillDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_SkillData.DT_SkillData'")));
	
	if (IsValid(SkillDataTable) == false)
		DEBUG_LOG("스킬 테이블 로드 실패");


	MakeSkillDictionary();

	ActionResourceTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ActionResource.DT_ActionResource'")));

	if (IsValid(ActionResourceTable) == false)
		DEBUG_LOG("액션 리소스 테이블 로드 실패");

	InputConfig = Cast<URLRInputConfig>(StaticLoadObject(URLRInputConfig::StaticClass(), NULL, TEXT("/Script/RLR.RLRInputConfig'/Game/Blueprints/Player/Input/RLRInputConfig.RLRInputConfig'")));
	if (IsValid(InputConfig) == false)
		DEBUG_LOG("키 입력 정보 로드 실패");


	ResourceTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ResourceData.DT_ResourceData'")));
	if (IsValid(ResourceTable) == false)
		DEBUG_LOG("텍스쳐 테이블 로드 실패");

	WidgetClassTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_WidgetClassData.DT_WidgetClassData'")));
	if (IsValid(WidgetClassTable) == false)
		DEBUG_LOG("위젯 클래스 테이블 로드 실패");

	CharacterClassTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_CharacterClassData.DT_CharacterClassData'")));
	if (IsValid(CharacterClassTable) == false)
		DEBUG_LOG("캐릭터 클래스 테이블 로드 실패");	
	
	ObjectClassTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ObjectClassData.DT_ObjectClassData'")));
	if (IsValid(ObjectClassTable) == false)
		DEBUG_LOG("오브젝트 클래스 테이블 로드 실패");

	LevelDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_LevelData.DT_LevelData'")));
	if (IsValid(LevelDataTable) == false)
		DEBUG_LOG("레벨 테이블 로드 실패");
	
	MonsterClassTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_MonsterClassData.DT_MonsterClassData'")));
	if (IsValid(MonsterClassTable) == false)
		DEBUG_LOG("몬스터 클래스 테이블 로드 실패");

	ExpDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ExpTable.DT_ExpTable'")));
	if(IsValid(ExpDataTable))
		DEBUG_LOG("경험치 데이터 테이블 로드 실패");

	AnimDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_AnimData.DT_AnimData'")));
	if (IsValid(AnimDataTable))
		DEBUG_LOG("애님 데이터 테이블 로드 실패");
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
			//분리 후 변경이 필요하다는게 무슨 의미일까? 나중에 민환님한테 물어보기.
			//ECharacterMainJobType MainJob = ECharacterMainJobType::NONE;

			ECharacterMainJobType MainJob = SkillData->MainJobType;

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
		TArray<FName> RowNames = ItemDataTable->GetRowNames();
		for (const FName& RowName : RowNames)
		{
			FItemData* Data = ItemDataTable->FindRow<FItemData>(RowName, TEXT("Searching by ITEM_SEQ"));
			if (Data && Data->ITEM_SEQ == Seq)
			{
				return *Data;
			}
		}
	}


	return FItemData();
}

FItemResource UDataManager::GetItemResource(int32 Seq)
{
	if (ItemResourceTable)
	{
		TArray<FName> RowNames = ItemResourceTable->GetRowNames();
		for (const FName& RowName : RowNames)
		{
			FItemResource* Data = ItemResourceTable->FindRow<FItemResource>(RowName, TEXT("Searching by ITEM_SEQ"));
			if (Data && Data->ITEM_SEQ == Seq) 
			{
				return *Data;
			}
		}
	}

	return FItemResource(); 
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

const FSkillData& UDataManager::GetSkillDataByTag(FGameplayTag Tag)
{
	if (SkillDataTable)
	{
		TArray<FName> RowNames = SkillDataTable->GetRowNames();
		for (const FName& RowName : RowNames)
		{
			FSkillData* Data = SkillDataTable->FindRow<FSkillData>(RowName, TEXT("Searching by Tag"));
			if (Data && Data->SkillTag == Tag)
			{
				return *Data;
			}
		}
	}

	return FSkillData::EmptySkillData;
}

const FActionResource& UDataManager::GetActionResource(int32 Seq)
{
	if (ActionResourceTable)
	{
		FActionResource* Data = ActionResourceTable->FindRow<FActionResource>(*FString::FromInt(Seq), TEXT(""));
		if (Data == nullptr)
			return FActionResource::EmptyActionResource;
		return *Data;
	}
	return FActionResource::EmptyActionResource;
}

const FActionResource& UDataManager::GetActionResourceByTag(FGameplayTag Tag)
{
	if (ActionResourceTable)
	{
		TArray<FName> RowNames = ActionResourceTable->GetRowNames();
		for (const FName& RowName : RowNames)
		{
			FActionResource* Data = ActionResourceTable->FindRow<FActionResource>(RowName, TEXT("Searching by Tag"));
			if (Data && Data->ActionTag == Tag)
			{
				return *Data;
			}
		}
	}

	return FActionResource::EmptyActionResource;
}

void UDataManager::GetSkillListByJob(ECharacterMainJobType JobType, TArray<FSkillData>& OutArray)
{
	if(SkillDictionary.Contains(JobType) == false)
		return;

	OutArray = SkillDictionary[JobType].toArray();
}

const FLevelData& UDataManager::GetLevelData(int32 Seq)
{
	if (IsValid(LevelDataTable))
	{
		FLevelData* Data = LevelDataTable->FindRow<FLevelData>(*FString::FromInt(Seq), TEXT(""));
		if (Data == nullptr)
			return FLevelData::EmptyData;

		return *Data;
	}

	return FLevelData::EmptyData;
}

const FExpTable& UDataManager::GetExpData(int32 Seq)
{
	if (IsValid(ExpDataTable))
	{
		FExpTable* Data = ExpDataTable->FindRow<FExpTable>(*FString::FromInt(Seq), TEXT(""));
		if (Data == nullptr)
			return FExpTable::EmptyExpData;

		return *Data;
	}

	return FExpTable::EmptyExpData;
}

const FAnimData& UDataManager::GetAnimData(FGameplayTag Tag)
{
	if (AnimDataTable)
	{
		FAnimData* Data = AnimDataTable->FindRow<FAnimData>(*Tag.ToString(), TEXT(""));
		if (Data == nullptr)
			return FAnimData::EmptyAnimData;

		return *Data;
	}

	return FAnimData::EmptyAnimData;
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
