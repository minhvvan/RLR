// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/DataManager.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void UDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	//데이터 파일들을 읽어온다.

	ItemDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/ItemDataTable.ItemDataTable'")));
	if (IsValid(ItemDataTable) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("아이템 테이블 로드 실패."));
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
