// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRObjects/Characters/RLRMonster.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "GameManager/GameplayTagManager.h"

ARLRMonster::ARLRMonster()
{
}

void ARLRMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//FGameplayTagManager TagManager = FGameplayTagManager::Get();
	//ASC->AddGameplayTag(TagManager.Object_State_Hittable);
}

void ARLRMonster::BeginPlay()
{
	Super::BeginPlay();
}
