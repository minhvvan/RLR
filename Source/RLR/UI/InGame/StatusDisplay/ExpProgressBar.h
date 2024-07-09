// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "ExpProgressBar.generated.h"

/**
 * 
 */

 class UProgressBar;

UCLASS()
class RLR_API UExpProgressBar : public UBaseUI
{
	GENERATED_BODY()

public:


	UFUNCTION(BlueprintCallable)
	void SetExpPercent(float Value);




public:
	/*
		Bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UProgressBar> ExpProgressBar;
	
	
};
