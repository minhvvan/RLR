// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MainUI.h"
#include "GameplayTagContainer.h"
#include "BaseScreen.generated.h"

class UWidgetSwitcher;
class UDialogueUI;
class UPageSwitcher;

UCLASS()
class RLR_API UBaseScreen : public UMainUI
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UPageSwitcher> PageSwitcher;

public:
	virtual void NativeConstruct() override;

public:
	UWidget* GetPage(FGameplayTag tag);
	UWidget* GetActivePage();
	FGameplayTag GetActivePageTag();
	void SetActivePage(FGameplayTag tag);
	bool SetPageUI(FGameplayTag tag, TObjectPtr<UBaseUI> newPage);
	void AddPageUI(FGameplayTag tag, TObjectPtr<UBaseUI> newPage);

private:
	TMap<FGameplayTag, int> PageIndices;
	FGameplayTag ActivePageTag;
};
