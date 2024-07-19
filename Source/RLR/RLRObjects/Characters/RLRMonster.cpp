// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRObjects/Characters/RLRMonster.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "GameManager/GameplayTagManager.h"

#include "RLR.h"

ARLRMonster::ARLRMonster()
{

}

void ARLRMonster::SetStat(FMonsterStatus& Stat)
{
	StatSet = ASC->GetStatSet<UStatSetMonster>();
	if (StatSet == nullptr)
	{
		ASC->CreateStatSet<UStatSetMonster>();
		StatSet = ASC->GetStatSet<UStatSetMonster>();
	}

	StatSet->SetStatData(Stat);

	//--------------------------------
	// Test Log
	//--------------------------------
	if (StatSet)
	{
		RLR_LOG(LogRLR, Log, TEXT("---------------------------------"));
		RLR_LOG(LogRLR, Log, TEXT("Seq: %d"), StatSet->GetMonsterSeq());
		RLR_LOG(LogRLR, Log, TEXT("Name: %s"), *StatSet->GetMonsterName());
		RLR_LOG(LogRLR, Log, TEXT("Level: %d"), StatSet->GetMonsterLevel());
		RLR_LOG(LogRLR, Log, TEXT("HP: %d"), StatSet->GetMonsterHp());
		RLR_LOG(LogRLR, Log, TEXT("TransX: %f"), StatSet->GetMonsterTransX());
		RLR_LOG(LogRLR, Log, TEXT("TransY: %f"), StatSet->GetMonsterTransY());
		RLR_LOG(LogRLR, Log, TEXT("TransZ: %f"), StatSet->GetMonsterTransZ());
		RLR_LOG(LogRLR, Log, TEXT("Id: %lld"), StatSet->GetMonsterId());
		RLR_LOG(LogRLR, Log, TEXT("---------------------------------"));
	}
}

void ARLRMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//공격 가능 태그(현재 에디터에서 편집) 
	//FGameplayTagManager TagManager = FGameplayTagManager::Get();
	//ASC->AddGameplayTag(TagManager.Object_State_Hittable);
}

void ARLRMonster::BeginPlay()
{
	Super::BeginPlay();
}