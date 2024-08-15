// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager/RLRStruct.h"
#include "PlayerManager.generated.h"

class ARLRPlayerCharacter;

UCLASS()
class RLR_API UPlayerManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPlayerManager();

    void                  SetPlayerData(FUserCharacter PlayerData);

    ARLRPlayerCharacter*  GetPlayerCharacter();
    int32                 GetPlayerSeq();
    int32                 GetUserSeq();

    //UpdateStat
    void UpdatePlayerTotalStatus(const FTotalStatus& NewTotalStatus);
    void UpdatePlayerSetStatus(const FSetStatus& NewSetStatus);
    void UpdatePlayerExp(int32 NewExp);
    void UpdateTalent(const FTalent& NewTalent);

    //이동
    bool RequestMove(const FMoveResult& MoveResult);
    void UpdatePlayerTransform(const FVector& NewTransform);

    //재능
    bool RequestTalent(int TalentOrder);


private:
    UPROPERTY()
    TObjectPtr<ARLRPlayerCharacter> PlayerCharacter;

public:
    class UStatSetPlayer* GetStatSet();
};
