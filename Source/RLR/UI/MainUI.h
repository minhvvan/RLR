// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "GameManager/RLRStruct.h"
#include "GameManager/GameplayTagManager.h"

#include "Structs/UtilStructs.h"
#include "MainUI.generated.h"

/**
 * 
 */

 class USubUI;

UCLASS()
class RLR_API UMainUI : public UBaseUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void BindSubUI();
	virtual void RefreshUI() override;
	virtual void CloseUI();

	virtual bool IsOpenSubUI(FGameplayTag InputTag) { return false; }
	virtual bool ToggleSubUI(FGameplayTag InputTag) { return false; }
	virtual USubUI* GetSubUI(FGameplayTag InputTag) { return nullptr; }
	virtual USubUI* GetSubUI(EUIType Type){return SubUIMap[Type]; }
	virtual void OpenSubUI(FGameplayTag InputTag) {};
	virtual void CloseSubUI(FGameplayTag InputTag) {};

public:

	TMap<FGameplayTag , USubUI*> UserActionSubUI;
	TMap<EUIType, USubUI*>				SubUIMap;
};
