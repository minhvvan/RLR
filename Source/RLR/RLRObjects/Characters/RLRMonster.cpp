// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRObjects/Characters/RLRMonster.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSetMonster.h"
#include "GameManager/GameplayTagManager.h"
#include "UI/ASCWidgetComponent.h"
#include "RLR.h"

ARLRMonster::ARLRMonster()
{
	HpBar = CreateDefaultSubobject<UASCWidgetComponent>(TEXT("HpBar"));
	HpBar->SetupAttachment(RootComponent);
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 125.f));

	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	HpBar->SetDrawSize({ 90.f, 40.f });
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

	//--------------------------------
	// Test Log
	//--------------------------------
	if (statSet)
	{
		RLR_LOG(LogRLR, Log, TEXT("---------------------------------"));
		RLR_LOG(LogRLR, Log, TEXT("Seq: %d"), statSet->GetMonsterSeq());
		RLR_LOG(LogRLR, Log, TEXT("Name: %s"), *statSet->GetMonsterName());
		RLR_LOG(LogRLR, Log, TEXT("Level: %d"), statSet->GetMonsterLevel());
		RLR_LOG(LogRLR, Log, TEXT("HP: %d"), statSet->GetMonsterHp());
		RLR_LOG(LogRLR, Log, TEXT("TransX: %f"), statSet->GetMonsterTransform().X);
		RLR_LOG(LogRLR, Log, TEXT("TransY: %f"), statSet->GetMonsterTransform().Y);
		RLR_LOG(LogRLR, Log, TEXT("TransZ: %f"), statSet->GetMonsterTransform().Z);
		RLR_LOG(LogRLR, Log, TEXT("Id: %lld"), statSet->GetMonsterId());
		RLR_LOG(LogRLR, Log, TEXT("---------------------------------"));
	}
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