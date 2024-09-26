// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InputTransactionCost.generated.h"

class UEditableTextBox;

UCLASS()
class RLR_API UInputTransactionCost : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
    UEditableTextBox* TransactionCostInput;

private:
	UFUNCTION()
    void OnTransactionCostChanged(const FText& NewText);
};
