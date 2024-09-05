// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "NPCPurchaseTab.generated.h"

class UTileView;
class UTextBlock;
class UButton;

UCLASS()
class RLR_API UNPCPurchaseTab : public UBaseUI
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTileView> TVItem;	
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTileView> TVCart;	

	//payment
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtPurchaseMoney;	
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtAfterMoney;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> BtnBuy;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> BtnEmpty;	
	
	//Page
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> BtnFirst;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> BtnPrev;	
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> BtnNext;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> BtnLast;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtCurrentPage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtLastPage;

public:
	virtual void NativeConstruct() override;
	void SetItemList(const TArray<FItemData>* ItemData);

protected:
	UFUNCTION()
	void OnBuyClicked();

	UFUNCTION()
	void OnEmptyClicked();

	UFUNCTION()
	void OnFirstClicked();

	UFUNCTION()
	void OnPrevClicked();

	UFUNCTION()
	void OnNextClicked();

	UFUNCTION()
	void OnLastClicked();

	void UpdatePage();
	void UpdateCurrentPageText();
	void UpdateLastPageText();

	int CurrentPage = 1;
	int LastPage = 1;

	const int ItemNumPerPage = 10;

	TArray<FItemData> Items;
};
