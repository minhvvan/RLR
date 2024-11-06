// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/SkillManager.h"
#include "GameManager/MonsterManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/OtherUserManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/ObjectManager.h"
#include "GameManager/EffectManager.h"
#include "GameManager/LevelManager.h"
#include "GameManager/QuestManager.h"
#include "GameManager/LobbyManager.h"
#include "GameManager/PostalManager.h"
#include "GameManager/FriendManager.h"
#include "GameManager/PartyManager.h"
#include "GameManager/GuildManager.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "GameOptionData/GameOptionData.h"
#include "Kismet/GameplayStatics.h"
#include "Network/Handler/ClientPacketHandler.h"

UGameManager* GameInstance = nullptr;

void UGameManager::Init()
{
    Super::Init();
    // Ensure GameInstance is set
    GameInstance = this;
    ClientPacketHandler::Init();
    LoadGameOption();
    
}

void UGameManager::LoadComplete(const float LoadTime, const FString& MapName)
{
    Super::LoadComplete(LoadTime, MapName);
    UE_LOG(LogTemp, Log, TEXT("Level %s load completed!"), *MapName);

    GetLevelManager()->LoadComplete(LoadTime, MapName);
}

void UGameManager::SetUserSeq(int32 userSeq)
{
    this->UserSeq = userSeq;
}

void UGameManager::SetPlayerSeq(int32 playerSeq)
{
    this->PlayerSeq = playerSeq;
}

UDataManager* UGameManager::GetDataManager()
{
	UDataManager* DataManager = GetSubsystem<UDataManager>(this);
	if (IsValid(DataManager))
	{


		return DataManager;
	}

	UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetDataManager Error."));
	return nullptr;
}

UUIManager* UGameManager::GetUIManager()
{
    UUIManager* UIManager = GetSubsystem<UUIManager>(this);
    if (IsValid(UIManager))
    {
        return UIManager;
    }

    UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetUIManager Error."));
    return nullptr;
}

UInventoryManager* UGameManager::GetInventoryManager()
{
    UInventoryManager* Inven = GetSubsystem<UInventoryManager>(this);
    if (IsValid(Inven))
    {
        return Inven;
    }

    UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetInventoryManager Error."));
    return nullptr;
}

USkillManager* UGameManager::GetSkillManager()
{
    USkillManager* SkillManager = GetSubsystem<USkillManager>(this);
    if (IsValid(SkillManager))
    {
        return SkillManager;
    }

    UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetSkillManager Error."));
    return nullptr;
}

UNetworkManager* UGameManager::GetNetworkManager()
{
    UNetworkManager* NetworkManager = GetSubsystem<UNetworkManager>(this);
    if (IsValid(NetworkManager))
    {
        return NetworkManager;
    }

    UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetNetworkManager Error."));
    return nullptr;
}

UMonsterManager* UGameManager::GetMonsterManager()
{
    UMonsterManager* MonsterManager = GetSubsystem<UMonsterManager>(this);
    if (IsValid(MonsterManager))
    {
        return MonsterManager;
    }

    UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetMonsterManager Error."));
    return nullptr;
}

UOtherUserManager* UGameManager::GetOtherUserManager()
{
    UOtherUserManager* OtherUserManager = GetSubsystem<UOtherUserManager>(this);
    if (IsValid(OtherUserManager))
    {
        return OtherUserManager;
    }

    UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetOtherUserManager Error."));
    return nullptr;
}

UPlayerManager* UGameManager::GetPlayerManager()
{
    UPlayerManager* PlayerManager = GetSubsystem<UPlayerManager>(this);
    if (IsValid(PlayerManager))
    {
        return PlayerManager;
    }

    UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetPlayerManager Error."));
    return nullptr;
}

UObjectManager* UGameManager::GetObjectManager()
{
    UObjectManager* ObjectManager = GetSubsystem<UObjectManager>(this);
    if (IsValid(ObjectManager))
    {
        return ObjectManager;
    }

    UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetObjectManager Error."));
    return nullptr;
}

UQuestManager* UGameManager::GetQuestManager()
{
    UQuestManager* QuestManager = GetSubsystem<UQuestManager>(this);
    if (IsValid(QuestManager))
    {
        return QuestManager;
    }

    UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetQuestManager Error."));
    return nullptr;
}

UPostalManager* UGameManager::GetPostalManager()
{
    UPostalManager* PostalManager = GetSubsystem<UPostalManager>(this);
    if (IsValid(PostalManager))
    {
        return PostalManager;
    }
    UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetPostalManager Error."));
    return nullptr;
}

UFriendManager* UGameManager::GetFriendManager()
{
    UFriendManager* FriendManager = GetSubsystem<UFriendManager>(this);
    if (IsValid(FriendManager))
    {
        return FriendManager;
	}
	UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetFriendManager Error."));
    return nullptr;

}

UGuildManager* UGameManager::GetGuildManager()
{
    UGuildManager* GuildManager = GetSubsystem<UGuildManager>(this);
    if (IsValid(GuildManager))
    {
        return GuildManager;
    }
    UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetGuildManager Error."));
    return nullptr;
}

UPartyManager* UGameManager::GetPartyManager()
{
    UPartyManager* PartyManager = GetSubsystem<UPartyManager>(this);
    if (IsValid(PartyManager))
    {
        return PartyManager;
    }
    UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetPartyManager Error."));
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

UEffectManager* UGameManager::GetEffectManager()
{
    UEffectManager* EffectManager = GetSubsystem<UEffectManager>(this);
    if (IsValid(EffectManager))
    {
        return EffectManager;
    }

    UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetEffectManager Error."));
    return nullptr;
}

ULevelManager* UGameManager::GetLevelManager()
{
    ULevelManager* LevelManager = GetSubsystem<ULevelManager>(this);
    if (IsValid(LevelManager))
    {
        return LevelManager;
    }

    UUtilBlueprintFunctionLibrary::DebugLog(TEXT("GetLevelManager Error."));
    return nullptr;
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
