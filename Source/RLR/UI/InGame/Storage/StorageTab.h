// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "StorageTab.generated.h"

class UTileView;

UCLASS()
class RLR_API UStorageTab : public UBaseUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTileView> TVItem;
	
public:
	void ClearEntry();
	void SetSlotItemData(const FItemData& Item, int Idx);
	void UpdateAllItem(const TArray<FItemData>& Items, FGameplayTag Tag);
	
	UFUNCTION()
	void UpdatedStorageCallback(int PageIndex);

	void SetPageNum(int page);
	int GetPageNum() const;
	
protected:
	int PageNum = -1;
	
	const int StorageSlotRow = 7;
	const int StorageSlotColumn = 7;
};

