// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "Structs/ItemStructs.h"
#include "NPCShopBundlePurchase.generated.h"

class UButton;
class UEditableText;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FConfirmPurchase, const FItemData&, itemData, const FItemResource&, itemResource);

UCLASS()
class RLR_API UNPCShopBundlePurchase : public USubUI
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> BtnConfirm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> BtnCancel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> BtnIncrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> BtnDecrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEditableText> EdtAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ImgItem;

protected:
	UFUNCTION()
	void OnConfirmClicked();

	UFUNCTION()
	void OnCancelClicked();

	UFUNCTION()
	void OnIncreaseClicked();

	UFUNCTION()
	void OnDecreaseClicked();

	void UpdateAmountText();

public:
	void SetItemData(const FItemData& item, const FItemResource& itemResource);

	FConfirmPurchase OnConfirmPurchase;

protected:
	FItemData Item;
	FItemResource ItemResource;
};