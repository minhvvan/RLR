// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "WidgetSwitcherButton.generated.h"

UCLASS(editinlinenew)
class RLR_API UWidgetSwitcherButton : public UButton
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = Widget)
	int WidgetIndex = -1;

protected:
	virtual void PostLoad() override;

	UFUNCTION()
	void OnClickCallBack();
};
