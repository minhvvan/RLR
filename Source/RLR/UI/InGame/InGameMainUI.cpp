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

	/*
	StatSet에 묶여있는 Data들이 변경되면 업데이트할 UI들의 함수 Binding
	*/
	statSet->ClearBindFunc();
	statSet->OnChangedTotalStatus.AddDynamic(this, &UInGameMainUI::OnChangedTotalStatus);
	statSet->OnChangedSetStatus.AddDynamic(this, &UInGameMainUI::OnChangedSetStatus);
	statSet->OnChangedLevel.AddDynamic(this, &UInGameMainUI::OnChangedLevel);
	statSet->OnChangedExp.AddDynamic(this, &UInGameMainUI::OnChangedExp);
	statSet->OnChangedTalent.AddDynamic(this, &UInGameMainUI::OnChangedTalent);
}

bool UInGameMainUI::ToggleSubUI(FGameplayTag inputTag)
{
	USubUI* subUI = GetSubUI(inputTag);
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

USubUI* UInGameMainUI::GetSubUI(FGameplayTag InputTag)
{
	if (!UserActionSubUI.Contains(InputTag)) return nullptr;
	return UserActionSubUI[InputTag];
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
	int32 newExp = statSet->GetExp();
	StatusDisplayUI->UpdateExp(newExp);
}

void UInGameMainUI::OnChangedTalent()
{
	if (!ActionSystemComponent) return;

	UStatSetPlayer* statSet = ActionSystemComponent->GetStatSet<UStatSetPlayer>();
	FTalent newTalent = statSet->GetTalent();

	//TODO: 재능 관련 UI에서 변경하도록 함수 호출
	RLR_LOG(LogRLR, Log, TEXT("Talent: %s"), *newTalent.toString());
}

void UInGameMainUI::OnChangedLevel()
{
	if (!ActionSystemComponent) return;
	if (!StatusDisplayUI) return;

	UStatSetPlayer* statSet = ActionSystemComponent->GetStatSet<UStatSetPlayer>();
	int32 newLevel = statSet->GetLevel();
	StatusDisplayUI->UpdateLevel(newLevel);
}
