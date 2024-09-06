// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "NPCShopBundlePurchase.generated.h"

class UButton;

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

protected:
	UFUNCTION()
	void OnConfirmClicked();

	UFUNCTION()
	void OnCancelClicked();

public:
	void SetItemData(const FItemData& item);
};
