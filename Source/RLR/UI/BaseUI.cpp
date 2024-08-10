// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
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
