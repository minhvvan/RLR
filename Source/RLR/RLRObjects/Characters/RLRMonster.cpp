// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRObjects/Characters/RLRMonster.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSetMonster.h"
#include "GameManager/GameplayTagManager.h"
#include "UI/ASCWidgetComponent.h"
#include "Structs/MonsterStructs.h"
#include "RLR.h"

ARLRMonster::ARLRMonster()
{
}

void ARLRMonster::SetStat(FMonsterStatus& Stat)
{
	UStatSetMonster* statSet = ASC->GetStatSet<UStatSetMonster>();
	if (statSet == nullptr)
	{
		ASC->CreateStatSet<UStatSetMonster>();
		statSet = ASC->GetStatSet<UStatSetMonster>();
	}

	statSet->SetStatData(Stat);
}

void ARLRMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//공격 가능 태그(현재 에디터에서 편집) 
	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	ASC->AddGameplayTag(TagManager.Object_State_Hittable);
}

void ARLRMonster::BeginPlay()
{
	Super::BeginPlay();
}