// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "InGameMenuUI.generated.h"

/**
	메뉴탭을 모아놓은 UI.
 */

 class UInGameMenuTab;
 class UButton;

UCLASS()
class RLR_API UInGameMenuUI : public UBaseUI
{
	GENERATED_BODY()
	

	virtual void NativeConstruct() override;

	/*
		AddTab은 초기화시 순서 문제로 Blueprint 안에서 실행해준다.
	*/
	UFUNCTION(BlueprintCallable)
	void AddTab();
	void AddTabListElement(UInGameMenuTab* MenuTab, FText MenuTabName, FText ElementName, TFunction<void(UInGameMenuUI*)> StoredFunction);

public:

	void CloseAllTabList();
	
	UFUNCTION(BlueprintCallable)
	void OnUnhovered();


	/*
		Option Func
	*/

	void OnClickedGameMenu();
	void OnClickedCustomerService();
	void OnClickedEscape();

	void OnTest();

public:

	/*
		Bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UInGameMenuTab> ShopTab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UInGameMenuTab>ExpeditionTab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UInGameMenuTab> CharacterTab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UInGameMenuTab> AdventureTab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UInGameMenuTab> CommunityTab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UInGameMenuTab> GuidTab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UInGameMenuTab> OptionTab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> CheckUnhoveredButton;

	UPROPERTY()
	TArray<UInGameMenuTab*> TabList;

	/*
		Option Tab Text
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText OptionTabText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText OptionTab_GameMenuText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText OptionTab_CustomerServiceCenter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText OptionTab_EscapeText;

	/*
		Guid Tab Text
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText GuidTabText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TestText;
};
