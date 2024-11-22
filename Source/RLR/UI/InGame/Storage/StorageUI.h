// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "StorageUI.generated.h"

class UButton;
class UWidgetSwitcher;
class UWidgetSwitcherButton;
class UHorizontalBox;

UCLASS()
class RLR_API UStorageUI : public USubUI
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> BtnBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

public:
	virtual void NativeConstruct() override;

public:
	void SetStorageItems(const TArray<TArray<FItemData>>& StorageItems);
	void SetUnLockedPageNum();

protected:
	TArray<UWidget*> TabButtons;
	TArray<TArray<FItemData>> Items;

	int UnLockedPageNum = 1;
	const int MaxStoragePageNum = 3;

	virtual void RefreshUI() override;
};
