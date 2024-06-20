// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "GameOptionData/GameOptionData.h"
#include "GameManager.h"
#include <Kismet/GameplayStatics.h>

void UGameManager::Init()
{
    Super::Init();
    LoadGameOption();
}

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

UGameOptionData* UGameManager::GetGameOptionData()
{
	if (GameOptionData == nullptr)
	{
		LoadGameOption();

		if (GameOptionData == nullptr)
		{
			UUtilBlueprintFunctionLibrary::DebugLog(TEXT("LoadChatOption Fail. GameManager GetGameOptionData 확인."));
			return GameOptionData;
		}
	}

	return GameOptionData;
}

void UGameManager::SaveGameOption()
{
    UGameplayStatics::SaveGameToSlot(GameOptionData, UGameOptionData::SlotName, 0);
}

void UGameManager::LoadGameOption()
{
    FString SlotName = UGameOptionData::SlotName;
    bool Ret = UGameplayStatics::DoesSaveGameExist(SlotName, 0);

    //세이브 데이터가 있으면 불러오고, 없으면 임시적으로 새로 만든다
    if (Ret == true)
    {
        UGameOptionData* LoadGameOptionData = Cast<UGameOptionData>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

        if (IsValid(LoadGameOptionData) == false)
        {
            UUtilBlueprintFunctionLibrary::DebugLog(TEXT("LoadChatOption Fail. LoadGameOptionData Is Valid 확인."));
            return;
        }

        GameOptionData = LoadGameOptionData;
    }
    else if (Ret == false)
    {
        UGameOptionData* NewGameOptionData = Cast<UGameOptionData>(UGameplayStatics::CreateSaveGameObject(UGameOptionData::StaticClass()));
        if (IsValid(NewGameOptionData) == false)
        {
            UUtilBlueprintFunctionLibrary::DebugLog(TEXT("LoadChatOption Fail. NewGameOptionData Is Valid 확인."));
            return;
        }

        NewGameOptionData->Init();
        GameOptionData = NewGameOptionData;
    }

    //임시 코드.
    if (GameOptionData->ChatOption.bVisibleChatOption.Num() == 0)
        GameOptionData->Init();


}
