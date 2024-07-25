// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/InGameMainUI.h"
#include "UI/SubUI.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/InGame/CharacterStatus/CharacterStatusUI.h"
#include "UI/InGame/Inventory/ItemInformation.h"
#include "UI/InGame/CharacterStatus/CharacterStatusUI.h"
#include "UI/InGame/StatusDisplay/StatusDisplay.h"
#include "Blueprint/WidgetTree.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "RLR.h"

void UInGameMainUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInGameMainUI::SetActionSystemComponent(AActor* Owner)
{
	Super::SetActionSystemComponent(Owner);

	UStatSetPlayer* statSet = ActionSystemComponent->GetStatSet<UStatSetPlayer>();
	if (statSet == nullptr)
	{
		ActionSystemComponent->CreateStatSet<UStatSetPlayer>();
		statSet = ActionSystemComponent->GetStatSet<UStatSetPlayer>();
	}

	statSet->OnChangedTotalStatus.AddDynamic(this, &UInGameMainUI::OnChangedTotalStatus);
	statSet->OnChangedSetStatus.AddDynamic(this, &UInGameMainUI::OnChangedSetStatus);
	statSet->OnChangedExp.AddDynamic(this, &UInGameMainUI::OnChangedExp);
}

bool UInGameMainUI::ToggleSubUI(int inputID)
{
	USubUI* subUI = GetSubUI(inputID);
	if (!subUI) return false;

	bool bOpen = subUI->GetVisibility() == ESlateVisibility::Hidden;

	if (bOpen)
	{
		subUI->OpenUI();
	}
	else
	{
		subUI->CloseUI();
	}

	return bOpen;
}

USubUI* UInGameMainUI::GetSubUI(int inputID)
{
	EUIType inputKey = static_cast<EUIType>(inputID);

	if (!UserActionSubUI.Contains(inputKey)) return nullptr;
	return UserActionSubUI[inputKey];
}

void UInGameMainUI::OnChangedTotalStatus()
{
	if (!ActionSystemComponent) return;
	if (!StatusDisplayUI) return;
	if (!CharacterStatusUI) return;

	UStatSetPlayer* statSet = ActionSystemComponent->GetStatSet<UStatSetPlayer>();
	FTotalStatus totalStat = statSet->GetTotalStatus();

	StatusDisplayUI->UpdateTotalStat(totalStat);
	CharacterStatusUI->UpdateTotalStat(totalStat);
}

void UInGameMainUI::OnChangedSetStatus()
{
	if (!ActionSystemComponent) return;
	if (!CharacterStatusUI) return;

	UStatSetPlayer* statSet = ActionSystemComponent->GetStatSet<UStatSetPlayer>();
	FSetStatus setStat = statSet->GetSetStatus();

	//TODO: 상의후 변경
	//CharacterStatusUI->UpdateSetStatus(setStat);
}

void UInGameMainUI::OnChangedExp()
{
	if (!ActionSystemComponent) return;
	if (!StatusDisplayUI) return;

	UStatSetPlayer* statSet = ActionSystemComponent->GetStatSet<UStatSetPlayer>();
	float newExp = statSet->GetExp();
	float maxExp = 100.f;

	//TODO: Exp Max값 필요
	float percent = FMath::Clamp(newExp / maxExp, 0.f, 1.f);
	StatusDisplayUI->UpdateExp(percent);
}
