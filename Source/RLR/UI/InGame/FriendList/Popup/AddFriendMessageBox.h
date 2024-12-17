// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MessageBoxUI.h"
#include "AddFriendMessageBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCloseRequestUISignature, bool, bIsClosed);

class UComboBoxString;
class UEditableText;
/**
 * 친구 추가 시 뜨는 팝업
 */
UCLASS()
class RLR_API UAddFriendMessageBox : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnFriendNameTextChanged(const FText& Text);

	UFUNCTION()
	void OnConfirmButtonClicked();	
	UFUNCTION()
	void OnCancelButtonClicked();

	UFUNCTION()
	void ChangedSelection(FString SelectedOption, ESelectInfo::Type SelectionType);

	void InitComponents();

	FOnCloseRequestUISignature OnCloseRequestUISignature;
public:
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* GroupListDropDownBox;

	UPROPERTY(meta = (BindWidget))
	UEditableText* PlayerNameInputText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Placeholder;

	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;
};
