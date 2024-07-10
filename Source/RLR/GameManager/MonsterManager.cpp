// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/MonsterManager.h"
#include "RLRObjects/Characters/RLRMonster.h"
#include "RLR.h"

UMonsterManager::UMonsterManager()
{
	///TODO: MonsterClass Setting
	ConstructorHelpers::FClassFinder<ARLRMonster> MonsterClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Character/BP_Monster.BP_Monster_C'"));
	if (MonsterClass.Succeeded())
	{
		MonsterClasses.Add(TEXT("Monster"), MonsterClass.Class);
	}
}

void UMonsterManager::SetMonsterData(TArray<FMonsterStatus>& MonsterArray)
{
	//TODO: Monster 데이터 Init (Monsters)
	Monsters = MonsterArray;
	SpawnMonsters();
}

void UMonsterManager::SpawnMonsters()
{
	//TODO: Spawn Monster
	for (auto MonsterStat : Monsters)
	{
		if (!MonsterClasses.Contains(MonsterStat.MonsterName)) continue;

		auto World = GetWorld();
		if (!World) return;

		ARLRMonster* Monster = World->SpawnActorDeferred<ARLRMonster>(MonsterClasses[MonsterStat.MonsterName], FTransform::Identity);
		if (!Monster) return;
	
		//Set Stat
		Monster->SetStat(MonsterStat);

		//Finish Spawn
		FTransform SpawnLoc;
		SpawnLoc.SetLocation({ MonsterStat.MonsterTransX, MonsterStat.MonsterTransY, MonsterStat.MonsterTransZ });
		Monster->FinishSpawning(SpawnLoc);
	}
}