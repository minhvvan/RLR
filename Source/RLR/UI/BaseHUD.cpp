// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseHUD.h"

#include "UI/MainUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
	if (GameInstance)
	{
		GameInstance->GetUIManager()->OpenMainUI(MainUIClass);
	}
}
