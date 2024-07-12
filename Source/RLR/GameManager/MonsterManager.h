// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager/RLRStruct.h"
#include "MonsterManager.generated.h"

/**
 * 
 */

class ARLRMonster;
UCLASS()
class RLR_API UMonsterManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UMonsterManager();

	UFUNCTION()
	void SetMonsterData(TArray<FMonsterStatus>& MonsterArray);

protected:
	void SpawnMonsters();

private:
	TArray<FMonsterStatus> Monsters;

	//FString 보다 Enum이 좋을듯
	TMap<FString, TSubclassOf<ARLRMonster>> MonsterClasses;
};
