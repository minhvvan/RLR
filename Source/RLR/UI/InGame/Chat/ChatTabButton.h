// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "ChatTabButton.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMyButtonClicked, UChatTabButton*, Button);
/**
 * 
 */
UCLASS()
class RLR_API UChatTabButton : public UButton
{
	GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category = "Button")
    FOnMyButtonClicked OnMyButtonClicked;

    virtual void SynchronizeProperties() override;
    void SetIndex(int32 TabIndex);
    int32 GetIndex() const;
protected:
    UFUNCTION()
    void HandleOnClicked();

    UPROPERTY()
    int32 Tabindex;
};
