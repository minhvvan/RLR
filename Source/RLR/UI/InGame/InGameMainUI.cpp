// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/InGameMainUI.h"
#include "UI/SubUI.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/InGame/CharacterProfile/CharacterProfile.h"
#include "UI/InGame/Inventory/ItemInformation.h"
#include "UI/InGame/CharacterStatusDisplay/CharacterStatusDisplay.h"

#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"

#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "Player/RLRPlayerController.h"
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
	statSet->OnChangedTotalStatus.AddUniqueDynamic(this, &UInGameMainUI::OnChangedTotalStatus);
	statSet->OnChangedSetStatus.AddUniqueDynamic(this, &UInGameMainUI::OnChangedSetStatus);
	statSet->OnChangedLevel.AddUniqueDynamic(this, &UInGameMainUI::OnChangedLevel);
	statSet->OnChangedExp.AddUniqueDynamic(this, &UInGameMainUI::OnChangedExp);
	statSet->OnChangedTalent.AddUniqueDynamic(this, &UInGameMainUI::OnChangedTalent);
}

void UInGameMainUI::OnPageActivated()
{
	ChangeInputModeGameAndUI();
}

void UInGameMainUI::OnChangedTotalStatus()
{
	if (!ActionSystemComponent) return;
	auto CharacterStatusDisplayUI = GetSubUI<UCharacterStatusDisplay>(RLRTAG.UI_Character_StatusDisplay);
	if (!CharacterStatusDisplayUI) return;

	auto CharacterProfile = GetSubUI<UCharacterProfile>(RLRTAG.UI_Character_Profile);
	if (!CharacterProfile) return;

	UStatSetPlayer* statSet = ActionSystemComponent->GetStatSet<UStatSetPlayer>();
	FTotalStatus totalStat = statSet->GetTotalStatus();

	CharacterStatusDisplayUI->UpdateTotalStat(totalStat);
	CharacterProfile->UpdateTotalStat(totalStat);
}

void UInGameMainUI::OnChangedSetStatus()
{
	if (!ActionSystemComponent) return;
	auto CharacterProfile = GetSubUI<UCharacterProfile>(RLRTAG.UI_Character_Profile);
	if (!CharacterProfile) return;

	UStatSetPlayer* statSet = ActionSystemComponent->GetStatSet<UStatSetPlayer>();
	FSetStatus setStat = statSet->GetSetStatus();

	//TODO: 상의후 변경
	//CharacterProfile->UpdateSetStatus(setStat);
}

void UInGameMainUI::OnChangedExp()
{
	if (!ActionSystemComponent) return;
	auto CharacterStatusDisplayUI = GetSubUI<UCharacterStatusDisplay>(RLRTAG.UI_Character_StatusDisplay);
	if (!CharacterStatusDisplayUI) return;

	UStatSetPlayer* statSet = ActionSystemComponent->GetStatSet<UStatSetPlayer>();
	int32 newExp = statSet->GetExp();
	CharacterStatusDisplayUI->UpdateExp(newExp);
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
	auto CharacterStatusDisplayUI = GetSubUI<UCharacterStatusDisplay>(RLRTAG.UI_Character_StatusDisplay);
	if (!CharacterStatusDisplayUI) return;

	UStatSetPlayer* statSet = ActionSystemComponent->GetStatSet<UStatSetPlayer>();
	int32 newLevel = statSet->GetLevel();
	CharacterStatusDisplayUI->UpdateLevel(newLevel);
}
