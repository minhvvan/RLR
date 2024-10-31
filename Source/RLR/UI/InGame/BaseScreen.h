// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "GameplayTagContainer.h"
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
	virtual void NativeConstruct() override;

public:
	UWidget* GetPage(FGameplayTag tag);
	FGameplayTag GetActivePage();
	void SetActivePage(FGameplayTag tag);
	void SetPageUI(FGameplayTag tag, TObjectPtr<UDialogueUI> newDialogueUI);

private:
	TMap<FGameplayTag, int> PageIndices;
	FGameplayTag ActivePage;
};
