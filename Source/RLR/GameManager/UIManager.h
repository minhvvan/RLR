// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Network/Proto/Packet.pb.h"
#include "RLRStruct.h"
#include "Structs/ItemStructs.h"
#include "UI/InGame/BaseScreen.h"
#include "UI/SubUI.h"
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
	FGameplayTag				GetActivePageTag();

	template<typename T>
	TObjectPtr<T> GetSubUI(FGameplayTag UITag);

	USubUI* OpenSubUI(FGameplayTag UITag);
	void CloseSubUI(FGameplayTag UITag);

	template<typename T>
	TObjectPtr<T> OpenPage(FGameplayTag PageTag, TSubclassOf<UBaseUI> UIClass = nullptr);

	UFUNCTION()
	void ClosePage();

	void ToggleSubUI(FGameplayTag UITag);

private:
	UPROPERTY()
	TObjectPtr<UMainUI>			MainUI;

public:
	template<typename T = UMainUI>
	TObjectPtr<T> GetPage(FGameplayTag Page);

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
};

template<typename T>
inline TObjectPtr<T> UUIManager::GetSubUI(FGameplayTag UITag)
{
	UBaseScreen* BaseScreen = Cast<UBaseScreen>(MainUI);
	if (!BaseScreen) return nullptr;

	UMainUI* currentMainUI = Cast<UMainUI>(BaseScreen->GetActivePage());
	if (!currentMainUI) return nullptr;

	return currentMainUI->GetSubUI<T>(UITag);
}

template<typename T>
inline TObjectPtr<T> UUIManager::OpenPage(FGameplayTag PageTag, TSubclassOf<UBaseUI> UIClass)
{
	UBaseScreen* BaseScreen = Cast<UBaseScreen>(MainUI);
	if (!BaseScreen || UIClass == nullptr) return nullptr;

	UBaseUI* newPage = CreateWidget<UBaseUI>(GetWorld(), UIClass);
	if (!BaseScreen->SetPageUI(PageTag, newPage)) return nullptr;

	BaseScreen->SetActivePage(PageTag);
	return GetPage<T>(PageTag);
}

template<typename T>
inline TObjectPtr<T> UUIManager::GetPage(FGameplayTag Page)
{
	UBaseScreen* BaseScreen = Cast<UBaseScreen>(MainUI);
	if (!BaseScreen) return Cast<T>(MainUI);
	return Cast<T>(BaseScreen->GetPage(Page));
}
