// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseHUD.h"

#include "UI/MainUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	auto DataManager = GameInstance->GetDataManager();
	if (!DataManager)
	{
		//TODO: 예외 처리(e.g. 재시작)

	}

	auto baseScreenClass = DataManager->GetWidgetClass<UBaseUI>(TEXT("WBP_BaseScreen"));
	if (!baseScreenClass)
	{
		//TODO: 예외 처리(e.g. 재시작)
	}

	GameInstance->GetUIManager()->OpenMainUI(baseScreenClass);
}