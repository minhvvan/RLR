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

    void SetPlayerData(FUserCharacter PlayerData);

    //UpdateStat
    void UpdatePlayerTotalStatus(const FTotalStatus& NewTotalStatus);
    void UpdatePlayerSetStatus(const FSetStatus& NewSetStatus);
    void UpdatePlayerExp(int32 NewExp);

    //이동
    bool RequestMove(const FMoveResult& MoveResult);
    void UpdatePlayerTransform(const FVector& NewTransform);

private:
    UPROPERTY()
    TObjectPtr<ARLRPlayerCharacter> PlayerCharacter;

public:
    class UStatSetPlayer* GetStatSet();
};
