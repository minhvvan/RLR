// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "BaseScreen.generated.h"

class UWidgetSwitcher;
class UDialogueUI;
class UPageSwitcher;

UCLASS()
class RLR_API UBaseScreen : public UBaseUI
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UPageSwitcher> PageSwitcher;

public:
	UWidget* GetPage(EUIType type);
	EUIType GetActivePage();
	void SetActivePage(EUIType type);
	void SetDialogueUI(TObjectPtr<UDialogueUI> newDialogueUI);
};
