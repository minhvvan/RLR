// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Network/Proto/Packet.pb.h"
#include "RLRStruct.h"

#include "GameManager/GameplayTagManager.h"
#include "UIManager.generated.h"

/**
 
	UI를 관리할 매니저.

 */

class UBaseUI;
class UMainUI;
class USubUI;
class USlotUI;
class UDialogueUI;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatedPlayerInfo, FUserCharacter, NewPlayerInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatedPartyPlayerInfo, FUserCharacter, NewPlayerInfo);

UCLASS()
class RLR_API UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void OpenMainUI(TSubclassOf<UMainUI> UIClass);
	void OpenSubUINearTargetSlot(USlotUI* Target, EUIType SubUIType);		//해당 슬롯 옆에 Sub UI를 띄운다.
	void CloseSubUI(EUIType SubUIType);
	void SetZOrderToTop(USubUI* Target);

	void CloseFrontSubUI ();
	void CloseAllSubUI();

	UMainUI* GetMainUI();
	void ToggleSubUI(FGameplayTag UITag);

	void AdjustZOrder();

	TObjectPtr<UDialogueUI> OpenDialogue(TSubclassOf<UDialogueUI> UIClass);

protected:
	UFUNCTION()
	void OnDialogueEnded();

private:

	TObjectPtr<UMainUI> MainUI;	
	TObjectPtr<UDialogueUI> DialogueUI;
	TArray<USubUI*> SubUIStack;
	int32 ZOrder = 0;


public:
	/*
		Delegate
	*/

	FUpdatedPlayerInfo					UpdatedPlayerInfo;
	FUpdatedPartyPlayerInfo			UpdatedPartyPlayerInfo;

};
