// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Network/Proto/Packet.pb.h"
#include "RLRStruct.h"
#include "Structs/ItemStructs.h"
#include "UI/InGame/BaseScreen.h"
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
	//TODO: 유지
	void OpenMainUI(TSubclassOf<UBaseUI> UIClass);
	FGameplayTag				GetActivePageTag();

	template<typename T>
	TObjectPtr<T> GetSubUI(FGameplayTag UITag);


	//TODO: 삭제
	void AddUI(UBaseUI* BaseUI);
	TObjectPtr<UBaseUI>			CreateUI(FString WidgetName);

	UPROPERTY()
	TMap<EUIType, UBaseUI*>		UIMap;

	UPROPERTY()
	TObjectPtr<ULoadingScreen>	LoadingScreen;




	//TODO: 위치조정
	void OpenSubUINearTargetSlot(USlotUI* Target, EUIType SubUIType);		//해당 슬롯 옆에 Sub UI를 띄운다.
	void SetZOrderToTop(USubUI* Target);

	void CloseFrontSubUI();
	void CloseAllSubUI();
	void AdjustZOrder();
	void SetSubUIPosition(FGameplayTag UITag, FVector2D NewPos);

	void AddSaleItem(const FItemData& Item, const FItemResource& ItemResource);
	void RemoveSaleItem(const FItemData& Item);

	UPROPERTY()
	TArray<USubUI*>				SubUIStack;



	//TODO: 통합
	void OpenSubUI(FGameplayTag UITag);
	//UBaseUI* OpenUI(EUIType UIType);

	void CloseSubUI(FGameplayTag UITag);
	//void CloseSubUI(EUIType UIType);



	//TODO: 변경
	//OpenPage
	TObjectPtr<UDialogueUI>		OpenDialogue(TSubclassOf<UBaseUI> UIClass);

	//ClosePage(Default: InGame열어주기)
	UFUNCTION()
	void OnDialogueEnded();




	//TODO: 생각 중
	void ToggleSubUI(FGameplayTag UITag);

private:
	UPROPERTY()
	TObjectPtr<UMainUI>			MainUI;

public:
	template<typename T = UWidget>
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

//TODO: Dialogue::SubUI는 못받아오는 상태
template<typename T>
inline TObjectPtr<T> UUIManager::GetSubUI(FGameplayTag UITag)
{
	UMainUI* currentMainUI = GetPage<UMainUI>(FGameplayTagManager::Get().Page_InGame);
	if (!currentMainUI) return nullptr;

	return Cast<T>(currentMainUI->GetSubUI(UITag));
}

template<typename T>
inline TObjectPtr<T> UUIManager::GetPage(FGameplayTag Page)
{
	UBaseScreen* BaseScreen = Cast<UBaseScreen>(MainUI);
	if (!BaseScreen) return Cast<T>(MainUI);
	return Cast<T>(BaseScreen->GetPage(Page));
}
