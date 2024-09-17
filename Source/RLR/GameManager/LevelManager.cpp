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
	AsyncTask(ENamedThreads::GameThread, [this, LevelName]()
	{

			//TODO 깔끔하게 분류되게 해주기
			FText LevelText;
			if (LevelName == FName("Lobby"))
			{
				LevelText = FText::Format(FText::FromString("/Game/Map/Lobby/{0}"), FText::FromString(LevelName.ToString()));
			}
			else if (LevelName == FName("Title"))
			{
				LevelText = FText::Format(FText::FromString("/Game/Map/Title/{0}"), FText::FromString(LevelName.ToString()));
			}
			else if (LevelName == FName("InGame"))
			{
				LevelText = FText::Format(FText::FromString("/Game/Map/InGame/{0}"), FText::FromString(LevelName.ToString()));
			}
			else
			{
				LevelText = FText::FromString("/Game/StylizedProvencal/Maps/TestMap2");
			}

			FString LevelString = LevelText.ToString();

			LoadPackageAsync(LevelString,
				FLoadPackageAsyncDelegate::CreateLambda([=](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
					{
						if (Result == EAsyncLoadingResult::Failed)
						{
							//여기에 들어왔다는 건 패키징된 맵이 아니라는 소리니, 패키징 해줄 것.
							GameInstance->GetLevelManager()->LoadLevelCompleteDelegate.Unbind();
							UGameplayStatics::OpenLevel(GameInstance->GetWorld(), "Title");
							DEBUG_MESSAGE;
							return;
						}

						UGameplayStatics::OpenLevel(GameInstance->GetWorld(), LevelName);
					}),
				0,PKG_ContainsMap);
	});
			
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

	LoadLevel(FName(*Data.LevelName));
	return true;
}

bool ULevelManager::EnterLevel(FName LevelName, FString MainServerAddress, int32 MainPort, FString MonsterServerAddress, int32 MonsterPort)
{
	LoadLevelCompleteDelegate.BindLambda([MainServerAddress, MainPort, MonsterServerAddress, MonsterPort]()
		{
			GameInstance->GetNetworkManager()->ConnectToMonsterServer(MonsterServerAddress, MonsterPort);
			GameInstance->GetNetworkManager()->ConnectToMainServer(MainServerAddress, MainPort);
			GameInstance->GetNetworkManager()->SendServerRequest();
			GameInstance->GetNetworkManager()->SendUserQuestPacket();
			GameInstance->GetNetworkManager()->SendGetSkillPacket();
		});
	LoadLevel(LevelName);
	return true;
}

void ULevelManager::LoadComplete(const float LoadTime, const FString& MapName)
{
	if(LoadLevelCompleteDelegate.ExecuteIfBound())
	{
		LoadLevelCompleteDelegate.Unbind();
	}
}

