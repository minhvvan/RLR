// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/MonsterManager.h"
#include "RLRObjects/Characters/RLRMonster.h"
#include "Async/Async.h"
#include "ActionSystem/ActionSystemTypes.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSetMonster.h"
#include "RLR.h"
#include "Kismet/GameplayStatics.h"

UMonsterManager::UMonsterManager()
{
    ConstructorHelpers::FClassFinder<ARLRMonster> MonsterClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Character/BP_Monster.BP_Monster_C'"));
    if (MonsterClass.Succeeded())
    {
        MonsterClasses.Add(TEXT("그린 슬라임"), MonsterClass.Class);
    }
}

void UMonsterManager::SetMonsterData(TArray<FMonsterStatus>& MonsterArray)
{
    // MonsterArray 데이터를 SpawnQueue에 추가
    AddMonstersToSpawnQueue(MonsterArray);

    // 타이머를 설정하여 40초 뒤에 ProcessSpawnQueue 함수를 호출합니다.
    if (GEngine && GEngine->GameViewport)
    {
        UWorld* World = GEngine->GameViewport->GetWorld();
        if (World)
        {
            // 타이머 설정을 게임 스레드에서 실행하도록 람다 사용
            AsyncTask(ENamedThreads::GameThread, [this, World]()
                {
                    World->GetTimerManager().SetTimer(TimerHandle, this, &UMonsterManager::ProcessSpawnQueue, 3.0f, false);
                    //World->GetTimerManager().SetTimer(TimerHandle, this, &UMonsterManager::ProcessSpawnQueue, 15.0f, false);
                });
        }
    }
}

void UMonsterManager::AddMonstersToSpawnQueue(TArray<FMonsterStatus> MonstersToSpawn)
{
    FScopeLock Lock(&QueueMutex);
    SpawnQueue.Append(MonstersToSpawn);
}

void UMonsterManager::ProcessSpawnQueue()
{
    if (GEngine && GEngine->GameViewport)
    {
        UWorld* World = GEngine->GameViewport->GetWorld();
        if (World)
        {
            TArray<FMonsterStatus> MonstersToSpawn;

            {
                FScopeLock Lock(&QueueMutex);
                MonstersToSpawn = SpawnQueue;
                SpawnQueue.Empty(); // SpawnQueue 초기화
            }

            Monsters = MonstersToSpawn; // Monsters 배열에 데이터를 복사
            SpawnMonsters(); // Monsters 배열을 이용해 몬스터 소환
        }
    }
}

void UMonsterManager::SpawnMonsters()
{
    auto World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("World is null"));
        return;
    }

    for (auto MonsterStat : Monsters)
    {
        FString UniqueName = MonsterStat.MonsterName;

        if (!MonsterClasses.Contains(UniqueName))
        {
            UE_LOG(LogTemp, Error, TEXT("Monster class not found for %s"), *UniqueName);
            continue;
        }

        TSubclassOf<ARLRMonster> MonsterClass = MonsterClasses[UniqueName];
        if (!MonsterClass)
        {
            UE_LOG(LogTemp, Error, TEXT("MonsterClass is invalid for %s"), *UniqueName);
            continue;
        }

        UE_LOG(LogTemp, Warning, TEXT("Spawning Monster: %s at (%f, %f, %f)"), *UniqueName, MonsterStat.MonsterTransform.X, MonsterStat.MonsterTransform.Y, MonsterStat.MonsterTransform.Z);

        FTransform SpawnTransform;
        SpawnTransform.SetLocation(FVector(MonsterStat.MonsterTransform.X, MonsterStat.MonsterTransform.Y, MonsterStat.MonsterTransform.Z));
        SpawnTransform.SetRotation(FQuat::Identity);
        SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

        UE_LOG(LogTemp, Warning, TEXT("SpawnTransform Location: %s"), *SpawnTransform.GetLocation().ToString());
        UE_LOG(LogTemp, Warning, TEXT("SpawnTransform Rotation: %s"), *SpawnTransform.GetRotation().ToString());
        UE_LOG(LogTemp, Warning, TEXT("SpawnTransform Scale: %s"), *SpawnTransform.GetScale3D().ToString());

        if (!MonsterClass.Get())
        {
            UE_LOG(LogTemp, Error, TEXT("MonsterClass.Get() is null for %s"), *UniqueName);
            continue;
        }

        ARLRMonster* Monster = World->SpawnActorDeferred<ARLRMonster>(MonsterClass, SpawnTransform);
        if (!Monster)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to spawn Monster: %s"), *UniqueName);
            continue;
        }

        UE_LOG(LogTemp, Warning, TEXT("Monster successfully spawned: %s"), *UniqueName);

        Monster->SetStat(MonsterStat);
        Monster->FinishSpawning(SpawnTransform);

        MonsterInstances.Add(Monster);
    }
    //TODO: Server Test
    //AddMonstersToInstances();
}

const FVector UMonsterManager::GetMonsterTransformById(int MonsterId)
{
    FVector result = FVector::ZeroVector;

    for (auto monster : MonsterInstances)
    {
        UStatSetMonster* monsterStatSet = monster->GetActionSystemComponent()->GetStatSet<UStatSetMonster>();
        if (!monsterStatSet) continue;

        if (monsterStatSet->GetMonsterId() == MonsterId)
        {
            result = monsterStatSet->GetMonsterTransform();
        }
    }

    return result;
}

void UMonsterManager::AddMonstersToInstances()
{
    auto World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("World is null"));
        return;
    }

    TArray<AActor*> FoundMonsters;
    UGameplayStatics::GetAllActorsOfClass(World, ARLRMonster::StaticClass(), FoundMonsters);

    for (AActor* Actor : FoundMonsters)
    {
        ARLRMonster* Monster = Cast<ARLRMonster>(Actor);
        if (Monster)
        {
            MonsterInstances.Add(Monster);
            UE_LOG(LogTemp, Warning, TEXT("Monster %s added to MonsterInstances"), *Monster->GetName());
        }
    }
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

    //TODO: Server Test
    //stat->UpdateTransForm(x, y, z);
    /*AsyncTask(ENamedThreads::GameThread, [monster, x, y, z]()
        {
            monster->SetActorLocation(FVector(x, y, z));
        });*/
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
