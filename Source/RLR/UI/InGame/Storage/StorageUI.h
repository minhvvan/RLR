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

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> BtnDeposit;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> BtnWithdraw;	
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtBalance;

public:
	virtual void NativeConstruct() override;

public:
	void SetStorageItems(const TArray<TArray<FItemData>>& StorageItems);
	void SetUnLockedPageNum();

	virtual void OpenUI() override;
	virtual void CloseUI() override;

	UFUNCTION()
	void AddItem(const FItemData& Item);
	void SetSlotItem(int TabIdx, int slotIdx, const FItemData&Item);

	void SetBalance(int Balance);

protected:
	TArray<UWidget*> TabButtons;
	TArray<TArray<FItemData>> Items;

	int UnLockedPageNum = 1;
	int MaxStoragePageNum = 5;
	const int MaxStorageSlotNum = 50;

	void Init();

	virtual void RefreshUI() override;

	UFUNCTION()
	void OnDepositClicked();

	UFUNCTION()
	void OnWithdrawClicked();

	UFUNCTION()
	void RequestDeposit(class UMessageBoxUI* MessageBox);

	UFUNCTION()
	void RequestWithdraw(class UMessageBoxUI* MessageBox);
};
