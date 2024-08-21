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
    ARLRMonster* GetMonsterByMonsterId(int64 monsterId);
    void AddMonstersToSpawnQueue(TArray<FMonsterStatus> MonstersToSpawn);

    //UpdateStat
    void UpdateMonsterTransform(int64 monsterId, float x, float y, float z);
    void UpdateMonsterHp(int64 monsterId, float newHp);
    void ApplyAbnormal(int64 monsterId, const FAbnormal2& abnormal);

    UFUNCTION()
    void SpawnMonsters();

    const FVector GetMonsterTransformById(int MonsterId);

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TArray<FMonsterStatus> Monsters;

    TArray<FMonsterStatus> SpawnQueue;
    FCriticalSection QueueMutex;


    UPROPERTY()
    TArray<ARLRMonster*> MonsterInstances;
    TMap<FString, TSubclassOf<ARLRMonster>> MonsterClasses;

    FTimerHandle TimerHandle; // 타이머 핸들 추가
    void AddMonstersToInstances();
    void ProcessSpawnQueue();
};
