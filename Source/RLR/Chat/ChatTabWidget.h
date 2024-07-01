// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include <Components/EditableTextBox.h>
#include <Components/Button.h>
#include "ChatTabButton.h"
#include "ChatTabWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMyButtonClickedSignature, int32, ButtonIndex);

UCLASS()
class RLR_API UChatTabWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    class UButton* ChattingTabButton;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ChattingTabText;

    UFUNCTION(BlueprintCallable)
    void SetTabName(const FText& InTabName);
    

   UPROPERTY(BlueprintAssignable, Category = "Button")
    FOnMyButtonClicked OnMyButtonClicked;

    UPROPERTY(BlueprintAssignable, Category = "UChatTabWidget")
    FMyButtonClickedSignature FMyButtonClickedSignature;

    UFUNCTION(BlueprintCallable, Category = "UChatTabWidget")
    void ClickButton(int32 ButtonIndex) const;



};
