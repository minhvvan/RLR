// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRObjects/Characters/RLRMonster.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSetMonster.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/QuestManager.h"
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
	MonsterID = Stat.MonsterSeq;

	statSet->OnOutOfHealth.AddDynamic(this, &ARLRMonster::SetDead);
	statSet->OnRevive.AddDynamic(this, &ARLRMonster::SetRevive);
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

void ARLRMonster::SetDead()
{
	Super::SetDead();
	if (auto* root = GetRootComponent())
	{
		root->SetVisibility(false, true);
	}
	/* QuestManager의 AddMonsterKillCountForAllQuests에 해당 몬스터 추가 */
	GameInstance->GetQuestManager()->AddMonsterKillCountForAllQuests(MonsterID);
}

void ARLRMonster::SetRevive()
{
	Super::SetRevive();
	if (auto* root = GetRootComponent())
	{
		root->SetVisibility(true, true);
	}
}
