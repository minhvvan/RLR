// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"

void UBaseUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseUI::CloseUI()
{
}

UUIManager* UBaseUI::GetUIManager()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());

	if (GM)
	{
		return GM->GetUIManager();
	}

	return nullptr;
}

UGameManager* UBaseUI::GetGameManager()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());

	if (GM)
	{
		return GM;
	}

	return nullptr;
}
