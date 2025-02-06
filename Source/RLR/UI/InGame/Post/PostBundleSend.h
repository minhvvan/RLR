// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "PostBundleSend.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FConfirmSendPostBundle, const FItemData&, itemData, int32, SlotIndex);

class UImage;
class UButton;
class UEditableText;
/**
 * 우편 번들 첨부 UI
 */
UCLASS()
class RLR_API UPostBundleSend : public USubUI
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
	void SetSlotIndex(int32 NewSlotIndex);
	void SetItemData(const FItemData& item);

	FConfirmSendPostBundle ConfirmSendPostBundle;

protected:
	FItemData Item;
	int32 slotIndex;
};
