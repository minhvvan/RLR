// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/LevelManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "Structs/LevelStruct.h"

#include "Kismet/GameplayStatics.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"


//bool ULevelManager::LoadLevel(FString LevelName)
//{
//	FName Level = FName(*LevelName);
//	return LoadLevel(Level);
//}

bool ULevelManager::LoadLevel(FName LevelName)
{
	UGameplayStatics::OpenLevel(this, LevelName);
	return true;
}

bool ULevelManager::LoadLevel(int32 LevelSeq)
{
	const FLevelData& Data = GameInstance->GetDataManager()->GetLevelData(LevelSeq);

	if (Data == FLevelData::EmptyData)
	{ 
		DEBUG_LOG("The level does not exist");
		return false;
	}

	UGameplayStatics::OpenLevel(this, FName(*Data.LevelName));
	return true;
}
