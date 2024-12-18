// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MessageBoxUI.h"
#include "MoveGroupMessageBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConfirmButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCancelButtonClicked);

class UComboBoxString;
class UTextBlock;
/**
 * 그룹 이동 시 뜨는 팝업
 */
UCLASS()
class RLR_API UMoveGroupMessageBox : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ConfirmButtonClicked();
	UFUNCTION()
	void CancelButtonClicked();

	FOnConfirmButtonClicked OnConfirmButtonClicked;
	FOnCancelButtonClicked OnCancelButtonClicked;
public:
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* GroupListDropDownBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerNameInputText;

	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;
};
