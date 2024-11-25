// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MessageBoxUI.h"
#include "GoodsMessageBox.generated.h"

class UEditableTextBox;
class UButton;

UCLASS()
class RLR_API UGoodsMessageBox : public UMessageBoxUI
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional))
	TObjectPtr<UEditableTextBox> EdtAmount;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional))
	TObjectPtr<UButton> BtnMax;

public:
	int GetAmount();

	virtual void OpenUI() override;

protected:
	int amount = 0;

	void SetAmountText();

	UFUNCTION()
	void OnMaxClicked();

	UFUNCTION()
	void OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);	
	
	UFUNCTION()
	void OnTextChanged(const FText& Text);
};
