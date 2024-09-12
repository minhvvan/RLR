// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/MonsterManager.h"
#include "RLRObjects/Characters/RLRMonster.h"
#include "Async/Async.h"
#include "ActionSystem/ActionSystemTypes.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSetMonster.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"
#include "RLR.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/MonsterStructs.h"

UMonsterManager::UMonsterManager()
{
}

void UMonsterManager::SetMonsterData(TArray<FMonsterStatus>& MonsterArray)
{
    FScopeLock Lock(&QueueMutex);
    Monsters.Append(MonsterArray);

    AsyncTask(ENamedThreads::GameThread, [this]()
    {
         SpawnMonsters();
    });
}

void UMonsterManager::SpawnMonsters()
{
    auto World = GetWorld();
    auto DataManager = GameInstance->GetDataManager();
    if (!World || !DataManager)
    {
        RLR_LOG(LogRLR, Error, TEXT("World is null"));
        return;
    }

    for (auto& MonsterStat : Monsters)
    {
        FString UniqueName = MonsterStat.MonsterName;
        auto MonsterClass = DataManager->GetMonsterClass<ARLRMonster>(MonsterStat.MonsterSeq);

        FTransform SpawnTransform;
        SpawnTransform.SetLocation(FVector(MonsterStat.MonsterTransform.X, MonsterStat.MonsterTransform.Y, MonsterStat.MonsterTransform.Z));
        SpawnTransform.SetRotation(FQuat::Identity);
        SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

        if (!MonsterClass.Get())
        {
            RLR_LOG(LogRLR, Error, TEXT("MonsterClass.Get() is null for %s"), *UniqueName);
            continue;
        }

        ARLRMonster* Monster = World->SpawnActorDeferred<ARLRMonster>(MonsterClass, SpawnTransform);
        if (!Monster)
        {
            RLR_LOG(LogRLR, Error, TEXT("Failed to spawn Monster: %s"), *UniqueName);
            continue;
        }

        Monster->SetStat(MonsterStat);
        Monster->FinishSpawning(SpawnTransform);

        MonsterInstances.Add(Monster);
    }
}

const FVector UMonsterManager::GetMonsterTransformById(int MonsterId)
{
    for (auto* monster : MonsterInstances)
    {
        if (!IsValid(monster))
        {
            UE_LOG(LogTemp, Warning, TEXT("Invalid monster instance found in MonsterInstances"));
            continue;
        }

        UActionSystemComponent* actionSystem = monster->GetActionSystemComponent();
        if (!actionSystem)
        {
            UE_LOG(LogTemp, Warning, TEXT("Monster %s has no ActionSystemComponent"), *monster->GetName());
            continue;
        }

        UStatSetMonster* monsterStatSet = actionSystem->GetStatSet<UStatSetMonster>();
        if (!monsterStatSet)
        {
            UE_LOG(LogTemp, Warning, TEXT("Monster %s has no StatSetMonster"), *monster->GetName());
            continue;
        }

        if (monsterStatSet->GetMonsterId() == MonsterId)
        {
            FVector monsterLocation = monster->GetActorLocation();

            // 비동기적으로 몬스터 제거 예약
            AsyncTask(ENamedThreads::GameThread, [this, monster]()
                {
                    if (IsValid(monster))
                    {
                        monster->SetLifeSpan(0.1f); // 0.1초 후에 제거
                        MonsterInstances.Remove(monster);
                    }
                });

            return monsterLocation;
            //return monster->GetActorLocation(); // 또는 monster->MonsterTransform 사용
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("No monster found with ID %d"), MonsterId);
    return FVector::ZeroVector;
}

ARLRMonster* UMonsterManager::GetMonsterByMonsterId(int64 monsterId)
{
    for (ARLRMonster* Monster : MonsterInstances)
    {  
        if (!Monster) {
            continue;
        }
        UStatSetMonster* status = Monster->GetActionSystemComponent()->GetStatSet<UStatSetMonster>();
        if (status->GetMonsterId() == monsterId)
        {
            return Monster;
        }
    }

    return nullptr;
}


void UMonsterManager::UpdateMonsterTransform(int64 monsterId, float x, float y, float z)
{
    ARLRMonster* monster = GetMonsterByMonsterId(monsterId);

    if (!monster)
    {
        UE_LOG(LogTemp, Error, TEXT("Monster is null"));
        return;
    }

    UActionSystemComponent* ActionSystem = monster->GetActionSystemComponent();
    if (!ActionSystem)
    {
        UE_LOG(LogTemp, Error, TEXT("ActionSystemComponent is null for Monster with ID: %lld"), monsterId);
        return;
    }

    UStatSetMonster* stat = ActionSystem->GetStatSet<UStatSetMonster>();
    if (!stat)
    {
        UE_LOG(LogTemp, Error, TEXT("StatSetMonster is null for Monster with ID: %lld"), monsterId);
        return;
    }

    FStatChangeSpec<FVector> spec;
    spec.ChangedStat = stat->GetMonsterTransformStat();
    spec.NewValue = FVector(x, y, z);

    stat->ApplyChangeStat(spec);
}

void UMonsterManager::UpdateMonsterHp(int64 monsterId, float newHp)
{
    ARLRMonster* monster = GetMonsterByMonsterId(monsterId);

    if (!monster)
    {
        UE_LOG(LogTemp, Error, TEXT("Monster is null"));
        return;
    }

    UActionSystemComponent* ActionSystem = monster->GetActionSystemComponent();
    if (!ActionSystem)
    {
        UE_LOG(LogTemp, Error, TEXT("ActionSystemComponent is null for Monster with ID: %lld"), monsterId);
        return;
    }

    UStatSetMonster* stat = ActionSystem->GetStatSet<UStatSetMonster>();
    if (!stat)
    {
        UE_LOG(LogTemp, Error, TEXT("StatSetMonster is null for Monster with ID: %lld"), monsterId);
        return;
    }

    FStatChangeSpec<int32> spec;
    spec.ChangedStat = stat->GetMonsterHpStat();
    spec.NewValue = newHp;

    stat->ApplyChangeStat(spec);
}

void UMonsterManager::ApplyAbnormal(int64 monsterId, const FAbnormal& abnormal)
{
    ARLRMonster* monster = GetMonsterByMonsterId(monsterId);

    if (!monster)
    {
        RLR_LOG(LogRLR, Error, TEXT("Monster is null"));
        return;
    }

    UActionSystemComponent* ActionSystem = monster->GetActionSystemComponent();
    if (!ActionSystem)
    {
        RLR_LOG(LogRLR, Error, TEXT("ActionSystemComponent is null for Monster with ID: %lld"), monsterId);
        return;
    }

    UStatSetMonster* stat = ActionSystem->GetStatSet<UStatSetMonster>();
    if (!stat)
    {
        RLR_LOG(LogRLR, Error, TEXT("StatSetMonster is null for Monster with ID: %lld"), monsterId);
        return;
    }

    stat->ApplyAbnormal(abnormal);
}
