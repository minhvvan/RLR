// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "DraggableWidget.generated.h"

/**
 * 
 */

 class UImage;
 class USizeBox;

UCLASS()
class RLR_API UDraggableWidget : public UBaseUI
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UImage> SlotImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<USizeBox> RootSizeBox;
	
};
