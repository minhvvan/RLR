// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "GameManager.h"

UDataManager* UGameManager::GetDataManager()
{
	UDataManager* DataManager = GetSubsystem<UDataManager>(this);
	if (IsValid(DataManager))
	{


		return DataManager;
	}

	UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetDataManager Error. GameManager.Cpp GetDataManager"));
	return nullptr;
}
