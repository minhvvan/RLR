// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/InventoryManager.h"

#include "ActionSystem/ActionSystemInterface.h"

void UBaseUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseUI::OpenUI()
{
	RefreshUI();
	SetVisibility(ESlateVisibility::Visible);
}

void UBaseUI::CloseUI()
{

	SetVisibility(ESlateVisibility::Hidden);
}

void UBaseUI::SetActionSystemComponent(AActor* Owner)
{
	IActionSystemInterface* ASCInterface = Cast<IActionSystemInterface>(Owner);
	if (!ASCInterface) return;

	UActionSystemComponent* ASC = ASCInterface->GetActionSystemComponent();
	if (!ASC) return;

	ActionSystemComponent = ASC;
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

UNetworkManager* UBaseUI::GetNetworkManager()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());

	if (GM)
	{
		return GM->GetNetworkManager();
	}

	return nullptr;
}

UPlayerManager* UBaseUI::GetPlayerManager()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());

	if (GM)
	{
		return GM->GetPlayerManager();
	}

	return nullptr;
}

USkillManager* UBaseUI::GetSkillManager()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());

	if (GM)
	{
		return GM->GetSkillManager();
	}

	return nullptr;
}

UInventoryManager* UBaseUI::GetInventoryManager()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());

	if (GM)
	{
		return GM->GetInventoryManager();
	}

	return nullptr;
}
