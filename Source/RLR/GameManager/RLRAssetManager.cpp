// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/RLRAssetManager.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/LiteralManager.h"

URLRAssetManager& URLRAssetManager::Get()
{
	check(GEngine);

	URLRAssetManager* Manager = Cast<URLRAssetManager>(GEngine->AssetManager);
	return *Manager;
}

void URLRAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	LiteralManager::Init();
	FGameplayTagManager::Init();
	//UAbilitySystemGlobals::Get().InitGlobalData();
}
