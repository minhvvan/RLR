// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "UI/SubUI.h"
#include "Player/PlayerCommands.h"
#include "KeyOption.generated.h"

/**
 * 
 */


 class UKeyOptionElement;
 class UButton;

UCLASS()
class RLR_API UKeyOption : public USubUI
{
	GENERATED_BODY()
	

	virtual void NativeConstruct() override;
	virtual void OpenUI() override;
	virtual void RefreshUI() override;

	UFUNCTION(BlueprintCallable)
	void LoadKeyOption();

	UFUNCTION(BlueprintCallable)
	void ApplyKeyOption();

	UFUNCTION(BlueprintCallable)
	void CreateDataAsset();


public:

	UFUNCTION(BlueprintCallable)
	void OnClickedConfirmButton();

	UFUNCTION(BlueprintCallable)
	void OnClickedCancelButton();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, UKeyOptionElement*> KeyOptionList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<URLRInputConfig> InputConfig;

	/*
		Bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UButton> ConfirmButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UButton> CancelButton;


};
