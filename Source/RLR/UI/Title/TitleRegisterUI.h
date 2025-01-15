// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleRegisterUI.generated.h"

/* 회원가입 취소 시 전달 -> TitleUI로 이동 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRegisterCancelButtonClicked);
/* 회원가입 완료 시 전달 -> TitleUI로 이동 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRegisterConfirmButtonClicked);

class UEditableTextBox;
class UButton;
/**
 * Title 화면에 띄워질 회원가입 UI
 */
UCLASS()
class RLR_API UTitleRegisterUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnCancelButtonClicked();
	
	UFUNCTION()
	void OnConfirmButtonClicked();

	FOnRegisterCancelButtonClicked OnRegisterCancelButtonClicked;
	FOnRegisterConfirmButtonClicked OnRegisterConfirmButtonClicked;

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> IDEditableTextBox;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> PWEditableTextBox;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ConfirmButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CancelButton;
};
