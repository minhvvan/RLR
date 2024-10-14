// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/PopupUI.h"
#include "MessageBoxUI.generated.h"

/**
	메시지 박스 UI 
	ex) 아이템 갯수 입력 UI.

 */

class UTextBlock;
class UButton;

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnButtonClicked, class UMessageBoxUI*, MessageBox);

UCLASS()
class RLR_API UMessageBoxUI : public UPopupUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void Init() override;
	virtual void RefreshUI() override;
	virtual void OpenUI();
	virtual void Clear() override;
	virtual void CloseUI();

public:

	UFUNCTION()
	virtual void OnClickedConfirmButton();
	UFUNCTION()
	virtual void OnClickedCancelButton();

public:

	virtual void SetText(FString MessageString);

public:
	/*
		bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> MessageText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional))
	TObjectPtr<UButton> ConfirmButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional))
	TObjectPtr<UButton> CancelButton;

public:
	
	UPROPERTY()
	FOnButtonClicked OnConfirmButtonClickedDelegate;

	UPROPERTY()
	FOnButtonClicked OnCancelButtonClickedDelegate;
};
