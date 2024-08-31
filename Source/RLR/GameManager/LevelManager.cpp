// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/LevelManager.h"

#include "Kismet/GameplayStatics.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"


//bool ULevelManager::LoadLevel(FString LevelName)
//{
//	FName Level = FName(*LevelName);
//	return LoadLevel(Level);
//}

bool ULevelManager::LoadLevel(FName LevelName)
{

	bool Ret = IsValidLevel(LevelName);
	if (Ret == false)
	{
		DEBUG_LOG("The Level does not exist.");
		return false;
	}

	UGameplayStatics::OpenLevel(this, LevelName);
	return true;
}

bool ULevelManager::IsValidLevel(FName LevelName)
{

}
