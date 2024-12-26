// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager/RLRStruct.h"
#include "Structs/ObjectStructs.h"
#include "Structs/PlayerStructs.h"
#include "PlayerManager.generated.h"

class ARLRPlayerCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdatePlayerManager);

UCLASS()
class RLR_API UPlayerManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPlayerManager();
    virtual void Initialize(FSubsystemCollectionBase& Collection);

public:

    void                  SetPlayerData(FUserCharacter PlayerData);
    
    ARLRPlayerCharacter*  GetPlayerCharacter();
    FUserCharacter        GetPlayerData();

    //UpdateStat
    void UpdatePlayerTotalStatus(const FTotalStatus& NewTotalStatus);
    void UpdatePlayerSetStatus(const FSetStatus& NewSetStatus);
    void UpdatePlayerExp(int32 NewExp);
    void UpdatePlayerLevel(int32 NewLevel );
    void UpdateTalent(const FTalent& NewTalent);
    void ApplyAbnormal(const FAbnormal& Abnormal);
    //이동
    bool RequestMove(const FMoveResult& MoveResult);
    void UpdatePlayerTransform(const FVector& NewTransform);

    void SpawnPlayerTransform(const FVector& NewTransform);

    //재능
    bool RequestTalent(int TalentOrder);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
    TSubclassOf<ARLRPlayerCharacter> PlayerCharacterClass;


    //재화
    void UpdateUserGood(FUserGoods userGood);

    void UpdatePlayerGood(FPlayerGoods playerGood);
    FUserGoods GetUserGood() const;
    FPlayerGoods GetPlayerGood() const;
private:
    UPROPERTY()
    TObjectPtr<ARLRPlayerCharacter> PlayerCharacter;

    FUserGoods UserGood;

    FPlayerGoods PlayerGood;

    FUserCharacter UserData;
public:
    class UStatSetPlayer* GetStatSet();

public:

	UPROPERTY()
    FUpdatePlayerManager UpdatePlayerManagerDelegate;
	void UpdatePlayerManagerBroadcast();
};
