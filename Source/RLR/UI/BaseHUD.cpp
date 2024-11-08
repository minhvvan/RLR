// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseHUD.h"

#include "UI/MainUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameplayTagManager.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	auto DataManager = GameInstance->GetDataManager();
	if (!DataManager) return;

	auto mainUIClass = DataManager->GetWidgetClass<UBaseUI>(MainUIClassName);
	if (!mainUIClass) return;
	
	GameInstance->GetUIManager()->OpenMainUI(mainUIClass);
}