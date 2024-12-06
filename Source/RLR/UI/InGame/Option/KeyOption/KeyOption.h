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
class RLR_API UKeyOption : public UBaseUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OpenUI() override;
	virtual void RefreshUI() override;

	UFUNCTION(BlueprintCallable)
	void LoadOption();

	UFUNCTION(BlueprintCallable)
	void ApplyOption();

	UFUNCTION(BlueprintCallable)
	void CreateDataAsset();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, UKeyOptionElement*> KeyOptionList;
};
