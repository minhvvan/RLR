// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/LevelManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/UIManager.h"
#include "Structs/LevelStruct.h"

#include "UI/LoadingScreen/LoadingScreen.h"

#include "Kismet/GameplayStatics.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Engine/LevelStreamingDynamic.h"

bool ULevelManager::LoadLevel(FName LevelName)
{
    GameInstance->GetUIManager()->OpenLoadingScreen();

    FText LevelText;
    if (LevelName == FName("Lobby"))
    {
        LevelText = FText::Format(FText::FromString("/Game/Map/Lobby/{0}"), FText::FromString(LevelName.ToString()));
    }
    else if (LevelName == FName("Title"))
    {
        LevelText = FText::Format(FText::FromString("/Game/Map/Title/{0}"), FText::FromString(LevelName.ToString()));
    }
    else if (LevelName == FName("Main"))
    {
        LevelText = FText::Format(FText::FromString("/Game/StylizedProvencal/Maps/{0}"), FText::FromString(LevelName.ToString()));
    };


    FString LevelString = LevelText.ToString();

    LoadPackageAsync(LevelString,
        FLoadPackageAsyncDelegate::CreateLambda([=](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
            {
                ULoadingScreen* LoadingScreen = GameInstance->GetUIManager()->GetLoadingScreen();

                LoadingScreen->SetLoadingResult(Result);
                if (Result == EAsyncLoadingResult::Succeeded)
                {
                    GameInstance->GetUIManager()->GetLoadingScreen()->SetNextLevel(LevelName);
                    DEBUG_LOG("Load Level Success");
                }
                else if (Result == EAsyncLoadingResult::Failed)
                {
                    GameInstance->GetUIManager()->GetLoadingScreen()->SetNextLevel(TEXT("Title"));
                    DEBUG_LOG("Load Level Fail");
                }
            }),
        0,
        PKG_ContainsMap);

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

	//LoadLevel(LevelName);
	return true;
}

void ULevelManager::LoadComplete(const float LoadTime, const FString& MapName)
{
    

	GameInstance->GetUIManager()->CloseLoadingScreen();
	LoadLevelCompleteDelegate.ExecuteIfBound();
	LoadLevelCompleteDelegate.Unbind();

  
}

