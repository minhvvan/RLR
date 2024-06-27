// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUI.generated.h"

/**

 */

 class UUIManager;

UCLASS()
class RLR_API UBaseUI : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void CloseUI();

public:

	UUIManager* GetUIManager();
};
