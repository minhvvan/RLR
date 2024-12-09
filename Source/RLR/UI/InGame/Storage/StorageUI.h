// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "StorageUI.generated.h"

class UButton;
class UTextBlock;
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

	UFUNCTION()
	void SetStorageAllItems();
	void SetUnLockedPageNum();

	UFUNCTION()
	virtual void InventorySlotShiftClicked(const FItemData& Item);

	void SetSlotItem(int TabIdx, int slotIdx, const FItemData&Item) const;
	int GetCurrentPage() const;

protected:
	TArray<UWidget*> TabButtons;

	const int MaxStorageTabNum = 5;
	const int MaxStorageSlotNum = 50;

	virtual void RefreshUI() override;

	UFUNCTION()
	virtual void InventoryToStorageMessageBoxCallback(class UMessageBoxUI* MessageBox);

protected:
	UStorageManager* StorageManager;
};