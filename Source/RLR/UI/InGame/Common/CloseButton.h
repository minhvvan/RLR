// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "CloseButton.generated.h"

/**
 * 
 */

 class UButton;

UCLASS()
class RLR_API UCloseButton : public UBaseUI
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void Init() override;

	UFUNCTION()
	void OnClickedCloseButton();
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

};
