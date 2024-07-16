// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "GameManager/RLRStruct.h"
#include "MainUI.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UMainUI : public UBaseUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void BindSubUI();
	virtual void CloseUI();

	virtual bool ToggleSubUI(int inputID) { return false; }
	virtual class USubUI* GetSubUI(int inputID) { return nullptr; }

public:

	TMap<EUIType, class USubUI*> UserActionSubUI;
};
