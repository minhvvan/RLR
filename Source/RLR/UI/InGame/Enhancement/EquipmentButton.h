// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ItemStructs.h"
#include "EquipmentButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipButtonClick, FItemData&, ItemData);


class UEnhanceSlot;
class UTextBlock;
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
	void SetItemData(const FItemData& NewItemData);
	void SetEnhanceSlot();
	FItemData GetItemData();

	UFUNCTION()
	void EquipButtonClicked();

	FOnEquipButtonClick OnEquipButtonClick;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* EquipButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEnhanceSlot> EnhanceSlot;

	UPROPERTY(meta =(BindWidget))
	UTextBlock* EnhanceLevelText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* EquipmentNameText;

private:
	int64 itemID;
	FItemData itemData;
};
