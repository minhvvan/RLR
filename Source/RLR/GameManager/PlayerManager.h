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

    UFUNCTION()
    void SetPlayerData(FUserCharacter PlayerData);

    //UpdateStat
    void UpdatePlayerTotalStatus(const FTotalStatus& NewTotalStatus);

private:
    UPROPERTY()
    TObjectPtr<ARLRPlayerCharacter> PlayerCharacter;
};
