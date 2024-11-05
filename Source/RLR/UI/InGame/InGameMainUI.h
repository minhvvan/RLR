// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameManager/RLRStruct.h"
#include "GameManager/GameplayTagManager.h"

#include "UI/MainUI.h"
#include "InGameMainUI.generated.h"

/**
 * 
 */

 class UChatUI;
 class UInventoryUI;
 class UChatOptionUI;
 class UEquipmentUI;
 class UItemInformation;
 class UCharacterStatusUI;
 class UMinimapUI;
 class UStatusDisplay;
 class UInGameMenuUI;
 class UPartyUI;
 class UKeyOption;
 class USkillUI;
 class USkillUpgrade;
 class UQuestListUI;
 class UPostOverlayUI;
 class UFriendListUI;
 class UOtherPlayerMenu;
 class UReportUI;
 class UCanvasPanel;
 class UTradeUI;
 class UItemCountMessageBox;
 class UNotificationMessageBox;
 class UConfirmMessageBox;
 class UGroupUI;

UCLASS()
class RLR_API UInGameMainUI : public UMainUI
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void SetActionSystemComponent(AActor* Owner) override;

protected:
	UFUNCTION()
	void OnChangedTotalStatus();

	UFUNCTION()
	void OnChangedSetStatus();	
	
	UFUNCTION()
	void OnChangedExp();	
	
	UFUNCTION()
	void OnChangedTalent();

	UFUNCTION()
	void OnChangedLevel();

	virtual void OnPageActivated() override;
};