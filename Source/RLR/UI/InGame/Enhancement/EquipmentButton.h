// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipButtonClick, int64, ItemID);

class UButton;

/**
 *	강화목록의 강화아이템
 */
UCLASS()
class RLR_API UEquipmentButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void SetItemID(int64 NewItemID);
	int64 GetItemID();

	UFUNCTION()
	void EquipButtonClicked();

	FOnEquipButtonClick OnEquipButtonClick;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* EquipButton;

private:
	int64 itemID;
};
