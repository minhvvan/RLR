// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Network/Proto/Packet.pb.h"
#include "RLRStruct.h"
#include "Structs/ItemStructs.h"
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
class ULoadingScreen;
class UPopupUI;
class UBaseScreen;
class UWidget;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatedPlayerInfo, FUserCharacter&, NewPlayerInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatedPartyPlayerInfo, FUserCharacter&, NewPlayerInfo);

UCLASS()
class RLR_API UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void OpenMainUI(TSubclassOf<UBaseUI> UIClass);
	UFUNCTION(BlueprintCallable)
	UBaseUI* OpenUI(EUIType UIType);
	void OpenSubUINearTargetSlot(USlotUI* Target, EUIType SubUIType);		//해당 슬롯 옆에 Sub UI를 띄운다.
	void SetZOrderToTop(USubUI* Target);

	void CloseFrontSubUI();
	void CloseAllSubUI();

	UMainUI* GetMainUI();
	UBaseUI* GetUI(EUIType UIType);
	void AddUI(UBaseUI* BaseUI);

	void ToggleSubUI(FGameplayTag UITag);
	void OpenSubUI(FGameplayTag UITag);
	void CloseSubUI(FGameplayTag UITag);
	void CloseSubUI(EUIType UIType);
	USubUI* GetSubUI(FGameplayTag UITag);

	void AdjustZOrder();
	void SetSubUIPosition(FGameplayTag UITag, FVector2D NewPos);

	TObjectPtr<UBaseUI>			CreateUI(FString WidgetName);
	TObjectPtr<UDialogueUI>		OpenDialogue(TSubclassOf<UBaseUI> UIClass);
	TObjectPtr<UDialogueUI>		GetDialogue();
	
	UFUNCTION()
	void OnDialogueEnded();

public:

	void AddSaleItem(const FItemData& Item, const FItemResource& ItemResource);
	void RemoveSaleItem(const FItemData& Item);

private:
	UPROPERTY()
	TObjectPtr<UBaseScreen>		BaseScreen;	

	UPROPERTY()
	TArray<UWidget*>			Pages;

	UPROPERTY()
	TObjectPtr<ULoadingScreen>	LoadingScreen;

	UPROPERTY()
	TArray<USubUI*>				SubUIStack;
	int32						ZOrder = 0;

	UPROPERTY()
	TMap<EUIType, UBaseUI*>		UIMap;

private:
	template<typename T = UWidget>
	T* GetPage(EUIType Type)
	{
		if (!Pages.IsValidIndex((int)Type)) return nullptr;
		return Cast<T>(Pages[(int)Type]);
	}

public:

	/*
		Title Delegate
	*/

	/*
		Lobby Delegate
	*/

	/*
		InGame Delegate
	*/
  
	FUpdatedPlayerInfo		UpdatedPlayerInfo;
	FUpdatedPartyPlayerInfo	UpdatedPartyPlayerInfo;

public:

	FTimerHandle				TimerHandle;
};
