// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/LevelManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/NetworkManager.h"
#include "Structs/LevelStruct.h"

#include "Kismet/GameplayStatics.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

bool ULevelManager::LoadLevel(FName LevelName)
{

	UGameplayStatics::OpenLevel(this, FName("InGame"));
	//UGameplayStatics::LoadStreamLevel(this, LevelName, true, true, FLatentActionInfo());
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

bool ULevelManager::EnterLevel(FName LevelName, FString MainServerAddress, int32 MainPort, FString MonsterServerAddress, int32 MonsterPort)
{
	//GameInstance->GetLevelManager()->LoadLevelCompleteDelegate.CreateLambda([&]()
	//	{
	//		GameInstance->GetNetworkManager()->ConnectToMonsterServer(MonsterServerAddress, MonsterPort);
	//		GameInstance->GetNetworkManager()->ConnectToMainServer(MainServerAddress, MainPort);
	//		GameInstance->GetNetworkManager()->SendServerRequest();
	//		GameInstance->GetNetworkManager()->SendGetSkillPacket();
	//		GameInstance->GetNetworkManager()->SendUserQuestPacket();
	//	});

	LoadLevel(LevelName);
	return true;
}

void ULevelManager::LoadComplete(const float LoadTime, const FString& MapName)
{
	LoadLevelCompleteDelegate.ExecuteIfBound();
	LoadLevelCompleteDelegate.Unbind();
}

